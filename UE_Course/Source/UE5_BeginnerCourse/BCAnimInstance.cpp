// Fill out your copyright notice in the Description page of Project Settings.


#include "BCAnimInstance.h"
#include "UE5_BeginnerCourseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void UBCAnimInstance::NativeBeginPlay()
{
	
	Super::NativeBeginPlay();
	player = Cast<AUE5_BeginnerCourseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	//player =  Cast<APlayerController>(TryGetPawnOwner());

	sideStrengthDefault = 50;
	sideStrength = sideStrengthDefault;
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

	isJumping = player->GetMovementComponent()->IsFalling();
	if(playerVelocity<=0)
	{
		sideStrength = sideStrengthDefault;
		return;
	}
	if(player->GetCurrentYaw()>0)
	{
		leaningState = ELeaningState::LS_LeanRight;
	}else if( player->GetCurrentYaw()<0)
	{
		leaningState = ELeaningState::LS_LeanLeft;
	}
	BeginTimeline();
	curveTimeline.TickTimeline(DeltaSeconds);

	
}

void UBCAnimInstance::BeginTimeline()
{
	if(curveTimeline.IsPlaying())
	{
		return;
	}
	FOnTimelineFloat timelineprogress;

	timelineprogress.BindUFunction(this, FName("TickTimeline"));

	curveTimeline.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
	curveTimeline.SetLooping(false);
	curveTimeline.AddInterpFloat(curveFloat, timelineprogress);
	curveTimeline.PlayFromStart();
}

void UBCAnimInstance::TickTimeline(float _deltaTime)
{
	switch (leaningState) {
	
	case ELeaningState::LS_LeanRight:
		if (sideStrength < 99.f)
			sideStrength = FMath::Lerp(sideStrength, sideStrength * 2, _deltaTime/100.f);
		break;
	case ELeaningState::LS_LeanLeft:
		if (sideStrength > 1.f)
		sideStrength = FMath::Lerp(sideStrength, 0, _deltaTime/100.f);
		break;
	default:
		sideStrength = sideStrengthDefault;
		break;
	}
}
