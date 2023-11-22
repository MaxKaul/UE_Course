// Fill out your copyright notice in the Description page of Project Settings.


#include "MyButton.h"

#include "UE5_BeginnerCourseCharacter.h"

AMyButton::AMyButton()
{
}

void AMyButton::OnPlayerInteract()
{
	Super::OnPlayerInteract();


	if(!buttonOwner)
	{
		
	}

	buttonOwner->ConditonCallback(bWasInteracted,buttonID);
	SetMaterialStatus();
}

void AMyButton::SetMaterialStatus()
{
	if (bWasInteracted)
	{
		objectMesh->SetMaterial(0, wasActivatedMat);
	}
	else if (!bWasInteracted)
	{
		objectMesh->SetMaterial(0, wasDeActivatedMat);
	}
}

void AMyButton::SetButtonInactive()
{

}


void AMyButton::BeginPlay()
{
	Super::BeginPlay();
	if (bWasInteracted)
	{
		objectMesh->SetMaterial(0, wasActivatedMat);
	}
	else if (!bWasInteracted)
	{
		objectMesh->SetMaterial(0, wasDeActivatedMat);
	}
}
