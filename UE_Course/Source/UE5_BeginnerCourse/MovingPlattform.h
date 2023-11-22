// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "Components/TimelineComponent.h"
#include "MovingPlattform.generated.h"

/**
 * 
 */
UCLASS()
class UE5_BEGINNERCOURSE_API AMovingPlattform : public AInteractableBase
{
	GENERATED_BODY()

		AMovingPlattform();

protected:
	virtual void OnPlayerInteraction_OnOverlapBegin(UPrimitiveComponent* _overlapComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIdx, bool _bFromSweep, const FHitResult& _sweepResult) override;
	virtual void OnPlayerInteraction_OnOverlapEnd(UPrimitiveComponent* _overlapComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIdx) override;

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void OnPlayerInteract() override;

	FORCEINLINE
		virtual bool GetConditionsMet() { return bConditionMet; }

	FORCEINLINE
		virtual void SetConditionsMet(bool _status) {  bConditionMet = _status; }

	FORCEINLINE
		virtual bool Conditional_Start_End() { return bConditional_Start_End; }
	FORCEINLINE
		virtual bool Conditional_End_Start() { return bConditional_End_Start; }

	UFUNCTION()
		void BeginTimeline();
	UFUNCTION()
		void TickTimeline(float _alpha);

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Infos, meta=(AllowPrivateAccess))
		float completionTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess))
		class ASplineClass* splineClassRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess))
		bool bHasReachedEnd;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess))
		float lerpDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess))
		class AUE5_BeginnerCourseCharacter* player;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess))
		bool bConditional_Start_End;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess))
		bool bConditional_End_Start;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess))
		bool bConditionMet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess))
		UCurveFloat* curveFloat;

	FTimeline curveTimeline;
};