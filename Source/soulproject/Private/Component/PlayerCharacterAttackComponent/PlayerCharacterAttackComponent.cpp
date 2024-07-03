#include "PlayerCharacterAttackComponent.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/EnemyCharacter/EnemyCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"
#include "../../Structure/AttackData/AttackData.h"
#include "AnimInstance/PlayerCharacter/PlayerCharacterAnimInstance.h"
#include "Object/CameraShake/AttackCameraShake.h"

#include "Widget/GameWidget/GameWidget.h"

#include "Components/StaticMeshComponent.h"
#include "Component/PlayerEquipWeaponComponent/PlayerEquipWeaponComponent.h"

#include "NiagaraSystem/AttackNiagaraSystem.h"

#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

UPlayerCharacterAttackComponent::UPlayerCharacterAttackComponent()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ATTACK_DATA(
		TEXT("/Script/Engine.DataTable'/Game/Resources/DataTable/DT_AttackData.DT_AttackData'"));
	if (DT_ATTACK_DATA.Succeeded())
	{
		DT_AttackData = DT_ATTACK_DATA.Object;
	}

	PrimaryComponentTick.bCanEverTick = true;

	bCheckingNextAttackInput = true;

	IsAttacking = false;

	IsAttackAreaEnabled = false;

	CriticalAttackPercentage = CRITICAL_ATTACK;
}

void UPlayerCharacterAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<AGameCharacter>(GetOwner());
}

void UPlayerCharacterAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AttackProcedure();
	CheckAttackArea();
}

void UPlayerCharacterAttackComponent::AttackProcedure()
{
	// 진행중인 공격이 있는가?
	if (CurrentAttackData != nullptr) return;

	// 요청된 공격이 있는가
	if (RequestAttackQueue.IsEmpty()) return;

	// 창 무기인지 먼저 확인합니다.
	CheckSpearAttack();

	AttackCode = Cast<AGameCharacter>(GetOwner())->GetCurrentWeaponCode();

	// 요청된 공격을 얻습니다.
	FAttackData* requestedAttack;
	RequestAttackQueue.Dequeue(requestedAttack);

	AttackDetectedActors.Empty();
	AttackDetectedEnemies.Empty();


	// 현재 공격을 요청된 공격으로 설정합니다.
	CurrentAttackData = GetAttackData();
	ApplyDamage = CurrentAttackData->AttackDamage;
	IsAttacking = true;

	// 카메라 앞을 바라보도록 설정된 경우, 카메라 앞을 보도록 합니다.
	if (CurrentAttackData->LookForward)
	{
		FRotator controlRotation = PlayerCharacter->GetControlRotation();
		controlRotation.Pitch = controlRotation.Roll = 0.0f;

		PlayerCharacter->SetActorRotation(controlRotation);
	}

	// 연계 공격임을 나타냅니다.
	bool isLinkAttack = false;

	if (PrevAttackData != nullptr)
		isLinkAttack = (PrevAttackData->AttackName == CurrentAttackData->AttackName);

	// 연계 공격이 아닌 경우 이전 공격을 초기화합니다.
	if (!isLinkAttack) PrevAttackData = nullptr;

	CurrentCombo = FMath::Clamp(CurrentCombo + 1, 0, TargetCombo);

	// 같은 공격을 진행하는 경우
	if (isLinkAttack)
	{


		int32 sectionNameIndex = CurrentCombo - 1;
		FName sectionName = CurrentAttackData->LinkableAttackSectionNames[sectionNameIndex];
		

		PlayerCharacter->PlayAnimMontage(CurrentAttackData->UseAnimMontage, 1.0f, sectionName);
	}
	else
	{
		// 공격을 시작합니다.
		PlayerCharacter->PlayAnimMontage(CurrentAttackData->UseAnimMontage);
	}
}

void UPlayerCharacterAttackComponent::CheckAttackArea()
{
	// 공격중이 아닌 경우 함수 호출 종료.
	if (!IsAttackAreaEnabled) return;

	float radius = 10.0f;

	if (PlayerCharacter->EquippedWeaponCode == _STORMBREAKER) radius = 30.0f;

	TArray<AActor*> actorsToIgnore;
	TArray<FHitResult> hitResults;


	UKismetSystemLibrary::SphereTraceMultiByProfile(
		this,
		CurrentStartSocketLocation,
		CurrentEndSocketLocation,
		radius,
		TEXT("AttackArea"),
		false,
		actorsToIgnore,
		EDrawDebugTrace::Type::ForDuration,
		hitResults,
		true, FLinearColor(0.0f, 0.0f, 0.0f, 0.0f), FLinearColor(), 0.0f);

	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetOwner());
	
	
	for (FHitResult& hit : hitResults)
	{
		enemyCharacter = Cast<AEnemyCharacter>(hit.GetActor());

		if (IsValid(enemyCharacter))
		{
			if (!AttackDetectedEnemies.Contains(enemyCharacter))
			{

				AttackDetectedEnemies.Add(enemyCharacter);

				// 치명타 공격인지 확인합니다.
				ApplyCriticalAttack();

				// 공격을 가한 위치를 저장합니다.
				AttackLocation = hit.Location;

				// 적 상태 위젯 띄우기
				AGamePlayerController* playerController =
					Cast<AGamePlayerController>(PlayerCharacter->GetController());

				if (IsValid(playerController))
					playerController->OnEnemyAttack(enemyCharacter);

				// 카메라 쉐이크 적용
				playerController->ClientStartCameraShake(UAttackCameraShake::StaticClass());

				// 나이아가라 시스템 적용
				playerCharacter->GetAttackNiagaraSystem()->ActivateNiagaraSystem();
				playerCharacter->GetAttackNiagaraSystem()->SetNiagaraSystemLocation(playerCharacter->GetActorLocation(), AttackLocation);

				if (IsCriticalAttack)
				{
					// 치명타 나이아가라 시스템 적용
					playerCharacter->GetAttackNiagaraSystem()->SetCriticalNiagaraSystemLocation(AttackLocation);

					// 치명타 위젯 적용
					playerController->GetGameWidget()->ShowCriticalAttackWidget();

				}

				// 적에게 가할 피해량 계산
				float damage = IsCriticalAttack ? 
					((Atk * 2.0f) + ApplyDamage) :
					(Atk * 0.5f) + ApplyDamage;

				UGameplayStatics::ApplyDamage(
					enemyCharacter,
					damage,
					PlayerCharacter->GetController(),
					PlayerCharacter,
					UDamageType::StaticClass());

			}

		}
		else
		{
			if (!AttackDetectedActors.Contains(hit.GetActor()))
			{
				AttackDetectedActors.Add(hit.GetActor());
				// 적 캐릭터 공격을 하는것이 아닐 때, 공격 막힘 애니메이션 재생
				Cast<AGameCharacter>(GetOwner())->PlayAttackBlockAnim ();

				UE_LOG(LogTemp, Warning, TEXT("hitResult = %s"), *hit.ToString());
				break;
			}

		}

	}
		

}

void UPlayerCharacterAttackComponent::CheckSpearAttack()
{
	AGameCharacter* gameCharacter = Cast<AGameCharacter>(GetOwner());
	FName equippedweapon = gameCharacter->EquippedWeaponCode;

	if (equippedweapon == TEXT("000004") || equippedweapon == TEXT("000005"))
	{
		gameCharacter->SetCurrentWeaponCode(WEAPON_SPEAR);
	}
	else if(equippedweapon == TEXT("000002") || equippedweapon == TEXT("000003"))
	{
		gameCharacter->SetCurrentWeaponCode(WEAPON_STORMBREAKER);
	}
	else  gameCharacter->SetCurrentWeaponCode(WEAPON_SHARPNER);


}

void UPlayerCharacterAttackComponent::ApplyCriticalAttack()
{
	// 1 ~ 100 중 랜덤한 정수값을 얻습니다.
	int32 randomNumber = FMath::RandRange(1, 100);
	UE_LOG(LogTemp, Warning, TEXT("CriticalAttackPercentage = %d"), CriticalAttackPercentage);

	IsCriticalAttack = (randomNumber <= CriticalAttackPercentage);

}



void UPlayerCharacterAttackComponent::UpdateAtk(float atk)
{
	Atk = atk;
}


void UPlayerCharacterAttackComponent::UpdateStaticWeaponSocketLocation(UStaticMeshComponent* weaponMesh)
{
	CurrentStartSocketLocation = weaponMesh->GetSocketTransform(WEAPON_SOCKET_START).GetLocation();
	CurrentEndSocketLocation = weaponMesh->GetSocketTransform(WEAPON_SOCKET_END).GetLocation();
}

void UPlayerCharacterAttackComponent::UpdateSkeletalWeaponSocketLocation(USkeletalMeshComponent* weaponMesh)
{
	CurrentStartSocketLocation = weaponMesh->GetSocketTransform(WEAPON_SOCKET_START).GetLocation();
	CurrentEndSocketLocation = weaponMesh->GetSocketTransform(WEAPON_SOCKET_END).GetLocation();

}

void UPlayerCharacterAttackComponent::ClearCurrentAttack()
{
	// 연계 공격이 끝난 경우
	if (CurrentCombo == TargetCombo)
	{
		CurrentCombo = TargetCombo = 0;
		PrevAttackData = CurrentAttackData = nullptr;
		IsAttacking = false;
		StartCheckingNextAttackInput();
	}
	else
	{
		PrevAttackData = CurrentAttackData;
		CurrentAttackData = nullptr;
	}
	ApplyDamage = 0.0f;
}

void UPlayerCharacterAttackComponent::CancelAttackState()
{
	// 공격 상태 비활성화
	IsAttacking = false;

	// 공격 데이터 비우기
	CurrentAttackData = nullptr;
	PrevAttackData = nullptr;

	// 콤보 초기화
	TargetCombo = CurrentCombo = 0;

	// 다음 공격 입력 체크 시작
	bCheckingNextAttackInput = true;
}

void UPlayerCharacterAttackComponent::RequestAttack(FName attackName)
{
	// 공격이 시작했음을 나타냅니다.
	isAttackStarted = true;

	// 공격 이름을 활용하여 공격 데이터 정보를 얻습니다.
	FString contextString;
	FAttackData* attackData = DT_AttackData->FindRow<FAttackData>(attackName, contextString);

	if (attackData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttackData is not valid %s"), *attackName.ToString());
		return;
	}

	if (bCheckingNextAttackInput)
	{
		// 목표 콤보를 증가시킵니다.
		if (attackData->GetMaxComboCount() > TargetCombo)
		{
			++TargetCombo;
		}
		else
		{
			return;
		}

		RequestAttackQueue.Enqueue(attackData);
	}

}

void UPlayerCharacterAttackComponent::StartCheckingNextAttackInput()
{
	bCheckingNextAttackInput = true;
}

void UPlayerCharacterAttackComponent::FinishCheckingNextAttackInput()
{
	bCheckingNextAttackInput = false;

	// 다음 공격이 존재하는 경우
	if (CurrentCombo < TargetCombo)
	{
		// 재생중이던 애니메이션 몽타주를 정지합니다.
		PlayerCharacter->StopAnimMontage();

		PrevAttackData = CurrentAttackData;
		CurrentAttackData = nullptr;
	}
}

void UPlayerCharacterAttackComponent::EnableAttackArea()
{
	IsAttackAreaEnabled = true;
}

void UPlayerCharacterAttackComponent::DisableAttackArea()
{
	IsAttackAreaEnabled = false;
}

void UPlayerCharacterAttackComponent::OnBlockStarted()
{
	BlockStartTime = GetWorld()->GetTimeSeconds();
	IsBlocking = true;
}

void UPlayerCharacterAttackComponent::OnBlockFinished()
{
	IsBlocking = false;
}

void UPlayerCharacterAttackComponent::SetCriticalAttackPercentage(int32 percent)
{
	CriticalAttackPercentage = percent;
}

FAttackData* UPlayerCharacterAttackComponent::GetAttackData()
{
	AGameCharacter* playerCharacter = Cast<AGameCharacter>(GetOwner());

	if (AttackCode.IsNone())
	{
		CurrentAttackData = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("AttackCode is not valid! "));
		return nullptr;
	}

	FAttackData* requestedAttack;
	FString contextstring;

	requestedAttack = DT_AttackData->FindRow<FAttackData>(AttackCode, contextstring);


	return requestedAttack;
}

