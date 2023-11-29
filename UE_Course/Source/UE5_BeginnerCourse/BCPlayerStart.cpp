// Fill out your copyright notice in the Description page of Project Settings.


#include "BCPlayerStart.h"

#include "UE5_BeginnerCourseCharacter.h"

void ABCPlayerStart::RespawnPlayer(AUE5_BeginnerCourseCharacter* _oldPlayer)
{
	_oldPlayer->Destroy();

	GetWorld()->SpawnActor<AUE5_BeginnerCourseCharacter>(player, GetActorLocation(), GetActorRotation());
}
