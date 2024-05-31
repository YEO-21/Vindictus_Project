#include "Structure/AttackData/AttackData.h"

FAttackData::FAttackData()
{
	AttackName = TEXT("");
	LinkableAttackSectionNames.Empty();
	UseAnimMontage = nullptr;
	AttackDamage = 0.0f;
	LookForward = false;

}
