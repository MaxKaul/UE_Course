// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "EnumLibrary.h"
#include "CoreMinimal.h"
#include "UE5_BeginnerCourseCharacter.h"
#include "Animation/AnimInstance.h"
#include <Components/TimelineComponent.h>
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerComps, meta = (AllowPrivateAccess))
	bool isJumping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerComps, meta = (AllowPrivateAccess))

	float sideStrength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerComps, meta = (AllowPrivateAccess))

	float sideStrengthDefault;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerComps, meta = (AllowPrivateAccess))
	UCurveFloat* curveFloat;
	FTimeline curveTimeline;
	ELeaningState leaningState;


	UFUNCTION()

		void BeginTimeline();

	UFUNCTION()
		void TickTimeline(float _deltaTime);
};


