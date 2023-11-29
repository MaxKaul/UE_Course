// Fill out your copyright notice in the Description page of Project Settings.


#include "MyButton.h"

#include "MovingPlattform.h"
#include "UE5_BeginnerCourseCharacter.h"

AMyButton::AMyButton()
{

}

void AMyButton::OnPlayerInteract()
{
	Super::OnPlayerInteract();

	if(!buttonOwner)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMyButton, !buttonOwner"));
		return;
	}

	SetMaterialStatus();

	buttonOwner->ConditionCallback(bWasInteracted, buttonID);
}

void AMyButton::SetMaterialStatus()
{
	if (bWasInteracted)
		objectMesh->SetMaterial(0, wasActivatedMat);
	else if (!bWasInteracted)
		objectMesh->SetMaterial(0, wasDeactivatedMat);
}

void AMyButton::SetButtonInactive()
{
	bWasInteracted = false;

	objectMesh->SetMaterial(0, wasDeactivatedMat);
}

void AMyButton::BeginPlay()
{
	Super::BeginPlay();

	if (bWasInteracted)
		objectMesh->SetMaterial(0, wasActivatedMat);
	else if (!bWasInteracted)
		objectMesh->SetMaterial(0, wasDeactivatedMat);
}
