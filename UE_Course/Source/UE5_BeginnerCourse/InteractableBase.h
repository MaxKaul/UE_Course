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
	// Sets default values for this actor's properties
	AInteractableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnPlayerInteraction_OnOverlapBegin(UPrimitiveComponent* _overlapComp,AActor* _otherActor,UPrimitiveComponent* _otherComp, int32 _otherBodyIdx, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()
	virtual void OnPlayerInteraction_OnOverlapEnd(UPrimitiveComponent* _overlapComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIdx);

	virtual void OnPlayerInteract();

	UPROPERTY(VisibleAnywhere,Category=Infos ,meta =(AllowPrivateAccess))
	bool bWasInteracted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
		class UBoxComponent* objectHitbox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
		UStaticMeshComponent* objectMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};



