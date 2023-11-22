// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ConditionLibrary.generated.h"


USTRUCT(BlueprintType)
struct FConditionRowBase:public FTableRowBase
{
	GENERATED_BODY()

		FConditionRowBase(){};

		UPROPERTY(EditAnywhere)
		TArray<int> conditionCombination;

};

USTRUCT(BlueprintType)
struct FConditionTableBase :public FTableRowBase
{
	GENERATED_BODY()

		FConditionTableBase(){};
		UPROPERTY(EditAnywhere)
		FName rowContent;


	UPROPERTY(EditAnywhere)
		TMap<int, FConditionRowBase> conditionMap;
};
