// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

UCLASS()
class UE5_BEGINNERCOURSE_API AInteractableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractableBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPlayerInteraction_OnOverlapBegin(UPrimitiveComponent* _overlapComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIdx, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()
	virtual void OnPlayerInteraction_OnOverlapEnd(UPrimitiveComponent* _overlapComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIdx);

public:
	UFUNCTION()
	virtual void OnPlayerInteract();

	UPROPERTY(VisibleAnywhere,Category = Infos, meta=(AllowPrivateAccess))
	bool bWasInteracted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
		class UBoxComponent* objectHitBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
		UStaticMeshComponent* objectMesh;

public:	
	virtual void Tick(float DeltaTime) override;

};
