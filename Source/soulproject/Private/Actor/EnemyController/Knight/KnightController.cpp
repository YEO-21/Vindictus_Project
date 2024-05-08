#include "Actor/EnemyController/Knight/KnightController.h"
#include "Actor/EnemyCharacter/Knight/KnightCharacter.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Component/KnightAttackComponent/KnightAttackComponent.h"

#include "Enum/CharacterTeam.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

void AKnightController::OnBlackboardKeyInitialize(UBlackboardComponent* blackboardComponent, APawn* inPawn)
{
	Super::OnBlackboardKeyInitialize(blackboardComponent, inPawn);

	BlackboardComponent = blackboardComponent;

	// MaxMoveDistance ����
	blackboardComponent->SetValueAsFloat(BLACKBOARDKEY_MAXMOVEDISTANCE, 2000.0f);
}

AKnightController::AKnightController()
{
	// �ڱ� ���� ������Ʈ�� ����
	UAIPerceptionComponent * perceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI_PERCEPTION"));
	// UAIPerceptionComponent : AI �� Ư�� �ڱ��� �����ϴ� ������Ʈ�Դϴ�.

	// ���� �ڱ� ���� ������Ʈ ��ü ����
	SetPerceptionComponent(*perceptionComponent);

	// �� ĳ������ ���� �����մϴ�.
	SetGenericTeamId(FGenericTeamId(ECharacterTeam::Enemy));

#pragma region ADD SIGHT PERCEPTION
	// �ð� �ڱ� ��ü ����
	AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SIGHT_PERCEPTION"));

	// �þ� �Ÿ��� �����մϴ�.
	AISightConfig->SightRadius = 400.0f;

	// �þ� ��� �Ÿ��� �����մϴ�.
	AISightConfig->LoseSightRadius = 800.0f;

	// �ڱ��� �Ҹ�Ǵ� �ð��� �����մϴ�.
	AISightConfig->SetMaxAge(5.0f);

	// �þ߰��� �����մϴ�. (120' ����)
	AISightConfig->PeripheralVisionAngleDegrees = 60.0f;

	// ���� �����ǵ��� �մϴ�.
	AISightConfig->DetectionByAffiliation.bDetectEnemies = true;

	// ���� ���� �������� �ʵ��� �մϴ�.
	AISightConfig->DetectionByAffiliation.bDetectFriendlies = false;

	// �߸� ���� �������� �ʵ��� �մϴ�.
	AISightConfig->DetectionByAffiliation.bDetectNeutrals = false;
#pragma endregion

	// �ش� ������ ����ϴ� �ð� �ڱ� ��ü�� �����մϴ�.
	GetPerceptionComponent()->ConfigureSense(*AISightConfig);

	// �þ߿� ��� ��ü�� ������ ��� �߻���ų �Լ��� ����մϴ�.
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(
		this, &ThisClass::OnSightUpdated);

}

void AKnightController::Attack()
{
	

	// Get KnightCharacter
	AKnightCharacter* controlledCharacter = Cast<AKnightCharacter>(GetPawn());

	// ��ȿ�� �˻�
	if (!IsValid(controlledCharacter)) return;


	// ����
	controlledCharacter->GetAttackComponent()->Attack();
}

void AKnightController::OnAttackFinished()
{

	if (!IsValid(BlackboardComponent)) return;

	BlackboardComponent->SetValueAsBool(KEYNAME_ISATTACKING, false);
}

void AKnightController::OnSightUpdated(AActor* actor, FAIStimulus stimulus)
{
	
	// ���������� ������ ���
	if (stimulus.WasSuccessfullySensed())
	{
		AGameCharacter* gameCharacter = Cast<AGameCharacter>(actor);
		if (!IsValid(gameCharacter)) return;

		BlackboardComponent->SetValueAsBool(BLACKBOARDKEY_ISAGGRESSIVESTATE, true);
		BlackboardComponent->SetValueAsObject(BLACKBOARDKEY_DAMAGEACTOR, gameCharacter);

		OnSightDetected.Broadcast();
	}
	// �������� ���� ���
	else
	{
		BlackboardComponent->SetValueAsBool(BLACKBOARDKEY_ISAGGRESSIVESTATE, false);

		OnSightLose.Broadcast();
	}
}
