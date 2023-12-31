// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interface_Damagable.h"
#include "UE5_BeginnerCourseCharacter.generated.h"


UCLASS(config=Game)
class AUE5_BeginnerCourseCharacter : public ACharacter, public IInterface_Damagable
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LeftClickAction;

public:
	AUE5_BeginnerCourseCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	void LookEnd(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Interact();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE
		float GetCurrentYaw() { return currYaw; }

	UFUNCTION(BlueprintCallable) FORCEINLINE
		void SetCurrentButton(class AMyButton* _currButton) { currentButton = _currButton; }

	UFUNCTION()
		void TakePlayerDamage(float _damage);

	UFUNCTION()
		void PlayPlayerDeath();
	UFUNCTION()
		void CleanAfterPlayerDeath();

	UFUNCTION() FORCEINLINE
		bool GetHasDied() {return bHasDied; }

	UFUNCTION(BlueprintCallable) FORCEINLINE
		float GetCurrentHealth() { return playerHealth; }

private:
	UPROPERTY()
		float currYaw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess))
		float playerHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess))
		bool bHasDied;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		TSubclassOf<class ABCPlayerStart> playerStartClass;

	UPROPERTY()
		class ABCPlayerStart* playerSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category=Comps, meta = (AllowPrivateAccess))
		class UPlayerInteractor* playerInteractor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comps, meta = (AllowPrivateAccess))
		class AMyButton* currentButton;

	UPROPERTY()
		USkeletalMeshComponent* playerMesh;
};