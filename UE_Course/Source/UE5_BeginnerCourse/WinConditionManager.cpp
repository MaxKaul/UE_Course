// Fill out your copyright notice in the Description page of Project Settings.


#include "WinConditionManager.h"

#include "MyButton.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWinConditionManager::AWinConditionManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWinConditionManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWinConditionManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if(!winButton)
	{
		UE_LOG(LogTemp,Warning,TEXT("AWinConditionManager, !winButton"))
		return;
	}

	if (winButton->WasInteracted() && !bGameWon)
		SetGameWon(0);
}

void AWinConditionManager::SetGameWon(int _playerId)
{
	bGameWon = true;

	UGameplayStatics::GetPlayerControllerFromID(GetWorld(), 0)->UnPossess();
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());

	if(!winScreenWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("AWinConditionManager, !winScreenWidget"));
		return;
	}

	winScreenWidget->AddToViewport();

	FInputModeUIOnly Inputmode;

	UGameplayStatics::GetPlayerControllerFromID(GetWorld(), 0)->SetInputMode(Inputmode);
	UGameplayStatics::GetPlayerControllerFromID(GetWorld(), 0)->SetShowMouseCursor(true);

}

void AWinConditionManager::SpawnWinButton()
{
	if(!winButtonClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("AWinConditionManager, !winButtonClass"));
		return;
	}

	if (!winButton)
		winButton = GetWorld()->SpawnActor<AMyButton>(winButtonClass, GetActorLocation(), GetActorRotation());
	else
		UE_LOG(LogTemp, Warning, TEXT("Button already spawned"));
}

