// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ELeaningState : uint8 {

	LS_DEFAULT,
	LS_LeanRight,
	LS_LeanLeft,
	LS_MAX_ENTRY
};
