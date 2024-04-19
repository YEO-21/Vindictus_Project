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
	// �������� ������ �ִ°�?
	if (CurrentAttackData != nullptr) return;

	// ��û�� ������ �ִ°�
	if (RequestAttackQueue.IsEmpty()) return;

	// ��û�� ������ ����ϴ�.
	FAttackData* requestedAttack;
	RequestAttackQueue.Dequeue(requestedAttack);

	AttackDetectedActors.Empty();
	AttackDetectedEnemies.Empty();


	// ���� ������ ��û�� �������� �����մϴ�.
	CurrentAttackData = requestedAttack;
	ApplyDamage = CurrentAttackData->AttackDamage;
	IsAttacking = true;

	// ī�޶� ���� �ٶ󺸵��� ������ ���, ī�޶� ���� ������ �մϴ�.
	if (CurrentAttackData->LookForward)
	{
		FRotator controlRotation = PlayerCharacter->GetControlRotation();
		controlRotation.Pitch = controlRotation.Roll = 0.0f;

		PlayerCharacter->SetActorRotation(controlRotation);
	}

	// ���� �������� ��Ÿ���ϴ�.
	bool isLinkAttack = false;

	if (PrevAttackData != nullptr)
		isLinkAttack = (PrevAttackData->AttackName == CurrentAttackData->AttackName);

	// ���� ������ �ƴ� ��� ���� ������ �ʱ�ȭ�մϴ�.
	if (!isLinkAttack) PrevAttackData = nullptr;

	CurrentCombo = FMath::Clamp(CurrentCombo + 1, 0, TargetCombo);

	// ���� ������ �����ϴ� ���
	if (isLinkAttack)
	{


		int32 sectionNameIndex = CurrentCombo - 1;
		FName sectionName = CurrentAttackData->LinkableAttackSectionNames[sectionNameIndex];
		PlayerCharacter->PlayAnimMontage(CurrentAttackData->UseAnimMontage, 1.0f, sectionName);
	}
	else
	{
		// ������ �����մϴ�.
		PlayerCharacter->PlayAnimMontage(CurrentAttackData->UseAnimMontage);
	}
}

void UPlayerCharacterAttackComponent::CheckAttackArea()
{
	// �������� �ƴ� ��� �Լ� ȣ�� ����.
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



				// �� ���� ���� ����
				AGamePlayerController* playerController =
					Cast<AGamePlayerController>(PlayerCharacter->GetController());

				if (IsValid(playerController))
					playerController->OnEnemyAttack(enemyCharacter);



				// ������ ���� ���ط� ���
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

				// �� ĳ���� ������ �ϴ°��� �ƴ� ��, ���� ���� �ִϸ��̼� ���
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
	// ���� ������ ���� ���
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
	// ���� ���� ��Ȱ��ȭ
	IsAttacking = false;

	// ���� ������ ������
	CurrentAttackData = nullptr;
	PrevAttackData = nullptr;

	// �޺� �ʱ�ȭ
	TargetCombo = CurrentCombo = 0;

	// ���� ���� �Է� üũ ����
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
		// ��ǥ �޺��� ������ŵ�ϴ�.
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

	// ���� ������ �����ϴ� ���
	if (CurrentCombo < TargetCombo)
	{
		// ������̴� �ִϸ��̼� ��Ÿ�ָ� �����մϴ�.
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

