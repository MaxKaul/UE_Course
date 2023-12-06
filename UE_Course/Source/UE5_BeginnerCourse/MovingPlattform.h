// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConditionLibrary.h"
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

	UFUNCTION()
		virtual void InitConditons();
	UFUNCTION()
		virtual void ResetConditons();
public:
	UFUNCTION()
		virtual void ConditonCallback(bool _status,int _objectID);

protected:
	UFUNCTION()
	
		virtual bool GetConditionsMet();

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		TArray<class AMyButton*> conditionButtons;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess))
		bool bConditionMet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess))
		UCurveFloat* curveFloat;

	FTimeline curveTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		class UDataTable* combiDataTable;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		FConditionRowBase activationCondition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		TArray<int> activationCombination_Fill;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		FName rowContentID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		int mapContentID;
};