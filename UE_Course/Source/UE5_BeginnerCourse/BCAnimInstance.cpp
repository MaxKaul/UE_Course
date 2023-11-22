// Fill out your copyright notice in the Description page of Project Settings.


#include "BCAnimInstance.h"

#include "UE5_BeginnerCourseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void UBCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	//player = Cast<AUE5_BeginnerCourseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	player = Cast<AUE5_BeginnerCourseCharacter>(TryGetPawnOwner());

	sideStrenghtDefault = 50.f;
	sideStrenght = sideStrenghtDefault;

	if (player)
		playerController = Cast<APlayerController>(player->GetController());
}

void UBCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!player || !playerController)
		return;

	FVector speed = player->GetVelocity();
	FVector lateralSpeed = FVector(speed.X, speed.Y, 0);

	playerVelocity = lateralSpeed.Size();
	bIsJumping = player->GetMovementComponent()->IsFalling();

	if(playerVelocity <= 0)
	{
		sideStrenght = sideStrenghtDefault;
		return;
	}

	if (player->GetCurrentYaw() > 0)
		leaningState = ELeaningState::LS_LeanRight;
	else if (player->GetCurrentYaw() < 0)
		leaningState = ELeaningState::LS_LeanLeft;

	BeginTimeline();
	curveTimeline.TickTimeline(DeltaSeconds);
}

void UBCAnimInstance::BeginTimeline()
{
	if (curveTimeline.IsPlaying())
		return;

	FOnTimelineFloat timelineprogress;

	timelineprogress.BindUFunction(this, FName("TickTimeline"));

	curveTimeline.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
	curveTimeline.SetLooping(false);

	curveTimeline.AddInterpFloat(curveFloat, timelineprogress);

	curveTimeline.PlayFromStart();
}

void UBCAnimInstance::TickTimeline(float _deltaTime)
{
	switch (leaningState)
	{
	case ELeaningState::LS_LeanRight:
		if (sideStrenght < 99.f)
			sideStrenght = FMath::Lerp(sideStrenght, sideStrenght * 2, _deltaTime / 100.f);
		break;
	case ELeaningState::LS_LeanLeft:
		if(sideStrenght > 1.f)
			sideStrenght = FMath::Lerp(sideStrenght, 0, _deltaTime / 100.f);
		break;

	default: 
		sideStrenght = sideStrenghtDefault;
		break;
		
	}
}
