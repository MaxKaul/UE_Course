// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE5_BeginnerCourseCharacter.h"
#include "Animation/AnimInstance.h"
#include "BCAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5_BEGINNERCOURSE_API UBCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:
	UPROPERTY()
	class AUE5_BeginnerCourseCharacter* player;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerComps, meta = (AllowPrivateAccess))

	APlayerController* playerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerComps, meta = (AllowPrivateAccess))

	float playerVelocity;


};


