// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WinConditionManager.generated.h"

UCLASS()
class UE5_BEGINNERCOURSE_API AWinConditionManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWinConditionManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WinConditions, meta = (AllowPrivateAccess))
		class AMyButton* winButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WinConditions, meta = (AllowPrivateAccess))

		TSubclassOf<AMyButton> winButtonClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WinConditions, meta = (AllowPrivateAccess))
		UUserWidget* winScreenWidget;
	UPROPERTY()
		bool bGamewon;
	UFUNCTION()
		void SetGameWon(int _playerID);

	UFUNCTION() FORCEINLINE

		bool GetWonGame() { return bGamewon; };

	UFUNCTION(CallInEditor, Category = WinConditions)
		void SPawnWinButton();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
