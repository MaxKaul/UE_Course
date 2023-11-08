// Fill out your copyright notice in the Description page of Project Settings.


#include "BCAnimInstance.h"
#include "UE5_BeginnerCourseCharacter.h"
#include "Kismet/GameplayStatics.h"

void UBCAnimInstance::NativeBeginPlay()
{
	
	Super::NativeBeginPlay();
	player = Cast<AUE5_BeginnerCourseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	//player =  Cast<APlayerController>(TryGetPawnOwner());
	if (player)
		playerController = Cast<APlayerController>(player->GetController());
}

void UBCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(!player||!playerController)
	{
		return;
	}

	FVector speed = player->GetVelocity();
	FVector lateralSpeed = FVector(speed.X, speed.Y, 0);
	playerVelocity = lateralSpeed.Size();

}
