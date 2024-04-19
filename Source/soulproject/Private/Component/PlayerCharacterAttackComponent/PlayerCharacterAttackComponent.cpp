#include "PlayerCharacterAttackComponent.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/EnemyCharacter/EnemyCharacter.h"
#include "Actor/PlayerController/GamePlayerController.h"
#include "../../Structure/AttackData/AttackData.h"
#include "AnimInstance/PlayerCharacter/PlayerCharacterAnimInstance.h"

#include "Components/StaticMeshComponent.h"

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

	// 요청된 공격을 얻습니다.
	FAttackData* requestedAttack;
	RequestAttackQueue.Dequeue(requestedAttack);

	AttackDetectedActors.Empty();
	AttackDetectedEnemies.Empty();


	// 현재 공격을 요청된 공격으로 설정합니다.
	CurrentAttackData = requestedAttack;
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

	TArray<AActor*> actorsToIgnore;
	TArray<FHitResult> hitResults;
	bool isHit = UKismetSystemLibrary::SphereTraceMultiByProfile(
		this,
		CurrentSaberStartSocketLocation,
		CurrentSaberEndSocketLocation,
		10.0f,
		TEXT("AttackArea"),
		false,
		actorsToIgnore,
		EDrawDebugTrace::Type::ForDuration,
		hitResults,
		true, FLinearColor(0.0f, 0.0f, 0.0f, 0.0f), FLinearColor(), 0.0f);
	
	for (FHitResult& hit : hitResults)
	{


		AEnemyCharacter* enemyCharacter = Cast<AEnemyCharacter>(hit.GetActor());
		

		if (IsValid(enemyCharacter))
		{
			if (!AttackDetectedEnemies.Contains(enemyCharacter))
			{
				AttackDetectedEnemies.Add(enemyCharacter);



				// 적 상태 위젯 띄우기
				AGamePlayerController* playerController =
					Cast<AGamePlayerController>(PlayerCharacter->GetController());

				if (IsValid(playerController))
					playerController->OnEnemyAttack(enemyCharacter);



				// 적에게 가할 피해량 계산
				float damage = (Atk * 0.5f) + ApplyDamage;

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
			if (!AttackDetectedActors.Contains(hit.GetActor()) && IsValid(hit.GetActor()))
			{
				AttackDetectedActors.Add(hit.GetActor());

				// 적 캐릭터 공격을 하는것이 아닐 때, 공격 막힘 애니메이션 재생
				Cast<AGameCharacter>(GetOwner())->PlayAttackBlockAnim();


				UE_LOG(LogTemp, Warning, TEXT("It is not EnemyCharacter"));
			}
			
		}

	}

}

void UPlayerCharacterAttackComponent::UpdateAtk(float atk)
{
	Atk = atk;
}


void UPlayerCharacterAttackComponent::UpdateWeaponSocketLocation(UStaticMeshComponent* weaponMesh)
{
	CurrentSaberStartSocketLocation = weaponMesh->GetSocketTransform(WEAPON_SOCKET_START).GetLocation();
	CurrentSaberEndSocketLocation = weaponMesh->GetSocketTransform(WEAPON_SOCKET_END).GetLocation();
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

	// 공격 데이터 비위기
	CurrentAttackData = nullptr;
	PrevAttackData = nullptr;

	// 콤보 초기화
	TargetCombo = CurrentCombo = 0;

	// 다음 공격 입력 체크 시작
	bCheckingNextAttackInput = true;
}

void UPlayerCharacterAttackComponent::RequestAttack(FName attackName)
{
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
		//PlayerCharacter->StopAnimMontage();

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

