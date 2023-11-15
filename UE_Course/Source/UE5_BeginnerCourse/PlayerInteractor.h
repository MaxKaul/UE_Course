// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_BEGINNERCOURSE_API UPlayerInteractor : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerInteractor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void TraceInteractable();

	UPROPERTY()
		UWorld* world;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess))
		class AUE5_BeginnerCourseCharacter* owner;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess))
		FVector2D crossHairSize;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess))
		float interactableRange;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
