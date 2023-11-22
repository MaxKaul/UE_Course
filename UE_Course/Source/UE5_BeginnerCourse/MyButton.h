// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "MovingPlattform.h"
#include "MyButton.generated.h"

/**
 * 
 */
UCLASS()
class UE5_BEGINNERCOURSE_API AMyButton : public AInteractableBase
{
	GENERATED_BODY()
		AMyButton();

public:
	UFUNCTION(BlueprintCallable) FORCEINLINE
		bool WasInteracted() { return bWasInteracted; }

	virtual void OnPlayerInteract() override;
	UFUNCTION()
		virtual void SetMaterialStatus();

	UFUNCTION()
		virtual void SetButtonInactive();

	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable) FORCEINLINE
		void SetButtonOwner(AMovingPlattform* _owner, int id) { buttonOwner = _owner, buttonID = id; };

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		UMaterialInterface* wasActivatedMat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		UMaterialInterface* wasDeActivatedMat;

	UPROPERTY()
		int buttonID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		AMovingPlattform* buttonOwner;
};
