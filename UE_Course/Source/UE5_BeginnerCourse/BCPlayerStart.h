// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "BCPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class UE5_BEGINNERCOURSE_API ABCPlayerStart : public APlayerStart
{
	GENERATED_BODY()
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comp, meta = (AllowPrivateAccess))
		TSubclassOf<class AUE5_BeginnerCourseCharacter> player;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comp, meta = (AllowPrivateAccess))
		float respawnTime;

public:
	UFUNCTION()

		void RespawnPlayer(AUE5_BeginnerCourseCharacter* _other);
	UFUNCTION() FORCEINLINE

		float GetRespawnTime() { return respawnTime; };
};
