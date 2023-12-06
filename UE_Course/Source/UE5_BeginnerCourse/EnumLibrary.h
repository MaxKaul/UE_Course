#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class ELeaningState : uint8
{
	LS_DEFAULT,
	LS_LeanRight,
	LS_LeanLeft,
	LS_MAX_ENTRY
};
//UENUM(BlueprintType)
//enum class EEnemyStates : uint8
//{
//	ES_DEFAULT,
//	ES_Patrol,
//	ES_HuntPLayer,
//	ES_AttackPlayer,
//	ES_MAX_ENTRY
//};