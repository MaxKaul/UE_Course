// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "MovingPlattform.h"
#include "MyButton.generated.h"

UCLASS()
class UE5_BEGINNERCOURSE_API AMyButton : public AInteractableBase
{
	GENERATED_BODY()

		AMyButton();

public:
	UFUNCTION(BlueprintCallable) FORCEINLINE
		bool WasInteracted() { return bWasInteracted; }

	UFUNCTION(BlueprintCallable) FORCEINLINE
		void SetButtonOwner(AMovingPlattform* _owner, int _id) { buttonOwner = _owner; buttonID = _id; }

	virtual void OnPlayerInteract() override;

	UFUNCTION()
		virtual void SetMaterialStatus();
	UFUNCTION()
		virtual void SetButtonInactive();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		UMaterialInterface* bWasActivatedMat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		UMaterialInterface* bWasDeactivatedMat;

	UPROPERTY()
		int buttonID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		class AMovingPlattform* buttonOwner;
};
