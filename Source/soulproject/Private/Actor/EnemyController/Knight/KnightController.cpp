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

	// MaxMoveDistance 설정
	blackboardComponent->SetValueAsFloat(BLACKBOARDKEY_MAXMOVEDISTANCE, 2000.0f);
}

AKnightController::AKnightController()
{
	// 자극 감지 컴포넌트를 생성
	UAIPerceptionComponent * perceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI_PERCEPTION"));
	// UAIPerceptionComponent : AI 의 특정 자극을 감지하는 컴포넌트입니다.

	// 사용될 자극 감지 컴포넌트 객체 설정
	SetPerceptionComponent(*perceptionComponent);

	// 적 캐릭터의 팀을 설정합니다.
	SetGenericTeamId(FGenericTeamId(ECharacterTeam::Enemy));

#pragma region ADD SIGHT PERCEPTION
	// 시각 자극 객체 생성
	AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SIGHT_PERCEPTION"));

	// 시야 거리를 설정합니다.
	AISightConfig->SightRadius = 400.0f;

	// 시야 상실 거리를 설정합니다.
	AISightConfig->LoseSightRadius = 800.0f;

	// 자극이 소멸되는 시간을 설정합니다.
	AISightConfig->SetMaxAge(5.0f);

	// 시야각을 설정합니다. (120' 감지)
	AISightConfig->PeripheralVisionAngleDegrees = 60.0f;

	// 적이 감지되도록 합니다.
	AISightConfig->DetectionByAffiliation.bDetectEnemies = true;

	// 같은 팀을 감지하지 않도록 합니다.
	AISightConfig->DetectionByAffiliation.bDetectFriendlies = false;

	// 중립 팀을 감지하지 않도록 합니다.
	AISightConfig->DetectionByAffiliation.bDetectNeutrals = false;
#pragma endregion

	// 해당 설정을 사용하는 시각 자극 객체를 적용합니다.
	GetPerceptionComponent()->ConfigureSense(*AISightConfig);

	// 시야에 어떠한 객체가 감지된 경우 발생시킬 함수를 등록합니다.
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(
		this, &ThisClass::OnSightUpdated);

}

void AKnightController::Attack()
{
	

	// Get KnightCharacter
	AKnightCharacter* controlledCharacter = Cast<AKnightCharacter>(GetPawn());

	// 유효성 검사
	if (!IsValid(controlledCharacter)) return;


	// 공격
	controlledCharacter->GetAttackComponent()->Attack();
}

void AKnightController::OnAttackFinished()
{

	if (!IsValid(BlackboardComponent)) return;

	BlackboardComponent->SetValueAsBool(KEYNAME_ISATTACKING, false);
}

void AKnightController::OnSightUpdated(AActor* actor, FAIStimulus stimulus)
{
	
	// 성공적으로 감지한 경우
	if (stimulus.WasSuccessfullySensed())
	{
		AGameCharacter* gameCharacter = Cast<AGameCharacter>(actor);
		if (!IsValid(gameCharacter)) return;

		BlackboardComponent->SetValueAsBool(BLACKBOARDKEY_ISAGGRESSIVESTATE, true);
		BlackboardComponent->SetValueAsObject(BLACKBOARDKEY_DAMAGEACTOR, gameCharacter);

		OnSightDetected.Broadcast();
	}
	// 감지하지 못한 경우
	else
	{
		BlackboardComponent->SetValueAsBool(BLACKBOARDKEY_ISAGGRESSIVESTATE, false);

		OnSightLose.Broadcast();
	}
}
