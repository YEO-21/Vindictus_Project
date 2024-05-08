#include "Actor/EnemyController/Golem/GolemController.h"
#include "Actor/GameCharacter/GameCharacter.h"
#include "Actor/EnemyCharacter/Golem/GolemCharacter.h"

#include "Component/GolemAttackComponent/GolemAttackComponent.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Enum/CharacterTeam.h"



AGolemController::AGolemController()
{
	
}

void AGolemController::OnBlackboardKeyInitialize(UBlackboardComponent* blackboardComponent, APawn* inPawn)
{
	Super::OnBlackboardKeyInitialize(blackboardComponent, inPawn);


	BlackboardComponent = blackboardComponent;

	// MaxMoveDistance 설정
	blackboardComponent->SetValueAsFloat(BLACKBOARDKEY_MAXMOVEDISTANCE, 5000.0f);

}

void AGolemController::SetAggressive(bool isAggressive, AActor* actor)
{
	BlackboardComponent->SetValueAsBool(BLACKBOARDKEY_ISAGGRESSIVESTATE, isAggressive);
	BlackboardComponent->SetValueAsObject(BLACKBOARDKEY_PLAYERCHARACTER, actor);
}

void AGolemController::Attack()
{
	AGolemCharacter* controlledGolem = Cast<AGolemCharacter>(GetPawn());

	if (!controlledGolem) return;
	

	// 공격 패턴1 ,2 중 하나를 랜덤으로 선택합니다.
	bool isAttack1 = FMath::RandBool();
	
	UE_LOG(LogTemp, Warning, TEXT("isAttack1 = %d"), isAttack1);

	if (!isAttackStarted)
	{
		if (isAttack1)
		{
			controlledGolem->GetGolemAttackComponent()->Attack(TEXT("GolemAttack1"));
			SetAttackState(true);
		}
		else
		{
			controlledGolem->GetGolemAttackComponent()->Attack(TEXT("GolemAttack2"));
			SetAttackState(true);
		}
	}
	
}

void AGolemController::FinishAttack()
{
	BlackboardComponent->SetValueAsBool(BLACKBOARDKEY_ISATTACKING, false);
	SetAttackState(false);
}

void AGolemController::SetAttackState(bool attackState)
{
	isAttackStarted = attackState;
}
