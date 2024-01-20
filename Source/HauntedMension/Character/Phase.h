// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "HauntedMension/Interfaces/HitInterface.h"
#include "HauntedMension/HMTypes/TurnInPlace.h"
#include "HauntedMension/HMTypes/HMTypes.h"
#include "Phase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChanged);

class IInteractInterface;
class UPawnNoiseEmitterComponent;
class UTraceComponent;
class AWeapon;
class UCameraComponent;
class AFlashLight;
class UInputAction;
class UInputMappingContext;
class UAnimMontage;
class USoundBase;
class AHMController;
class AHMHUD;
class UHMOverlay;
class USpringArmComponent;

UCLASS()
class HAUNTEDMENSION_API APhase : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	APhase();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetOverlappingInteractitem(class AInteract* Interact);

	void PlayPickUpMontage();

	void FlashOnOffPressed();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EKeyState KeyState = EKeyState::EKS_UnEquippedKey;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AFlashLight> EquippedFlashLight;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> Weapon;

protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Jump(const FInputActionValue& Value);

	void RunPressed();

	void RunReleased();

	void HideMeshifCameraClose();

	void InteractPressed();

	void AimPressed();

	void AimReleased();

	void InterpFOV(float DeltaTime);

	void PlayReloadMontage();

	void PlayHitMontage(const FVector& ImpactPoint);

	void ReloadPressed();

	void FinishReload();

	void FirePressed();

	void TraceCrossHair(FHitResult& TraceHitResult);

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	void SetActionState();

	void UpdateHUDAmmo();

	void UpdateHUDCarriedAmmo();

	bool CanFire();

	bool CanReload();

	void InitializeComponent();

	UFUNCTION(BlueprintCallable)
	void EndPickUp();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Die();

	UFUNCTION(BlueprintCallable)
	void FallEquipped();

	UFUNCTION(BlueprintCallable)
	void AttachToFlashLight();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTraceComponent> TraceComponent;

	UPROPERTY(VisibleAnywhere)
	FVector HitTarget;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TScriptInterface<IInteractInterface> InteractItem;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AWeapon> DefaultWeapon;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AAmmoPickUp> AmmoPickup;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EFlashLightState FlashLightState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EDeathState DeathState = EDeathState::EDS_Alive;

	// Turn In Place 

	UPROPERTY(VisibleAnywhere)
	ETurnInPlace TurnInPlace;

	void AimOffset(float DeltaTime);

	float CalculateSpeed();

	void TurningInPlace(float DeltaTime);

	float AO_Yaw;
	float AO_Pitch;
	float Interp_AO_Yaw;

	FRotator StartAimRotation;

	bool bRotateRootBone;

	// Input

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> CharacterMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> RunPressedAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> RunReleasedAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> FlashOnOffAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> AimPressedAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> AimReleasedAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ReloadAction;

	// AnimMontage

	UPROPERTY(EditAnywhere, Category = "AnimMontage")
	TObjectPtr<UAnimMontage> PickupMontage;

	UPROPERTY(EditAnywhere, Category = "AnimMontage")
	TObjectPtr<UAnimMontage> ReloadMontage;

	UPROPERTY(EditAnywhere, Category = "AnimMontage")
	TObjectPtr<UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, Category = "AnimMontage")
	TObjectPtr<UAnimMontage> DeathMontage;

	// Sound

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> NoAmmoSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> HitSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> BreathSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<UAudioComponent> BreathSoundComponent;

	UPROPERTY(EditAnywhere)
	bool IsPlayingBreathSound = false;

	// FOV
	
	float DefaultFOV;

	float CurrentFOV;

	UPROPERTY(EditAnywhere)
	float ZoomedFOV = 30.f;

	UPROPERTY(EditAnywhere)
	float ZoomInterpSpeed = 30.f;


	UPROPERTY(EditAnywhere)
	float CameraDistanceThresHold = 150.f;

	UPROPERTY(EditAnywhere)
	float HP = 100.f;

	UPROPERTY(EditAnywhere)
	float MaxHP = 100.f;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY()
	TObjectPtr<AHMController> HMController;

	UPROPERTY()
	TObjectPtr<AHMHUD> HMHUD;

	UPROPERTY()
	TObjectPtr<UHMOverlay> HMOverlay;

	FTimerHandle HitHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAttributeComponent> StatComponent;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bAiming = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsSequenceUse = false;

	UPROPERTY(EditAnywhere)
	float HitDelay = 0.2f;

	UPROPERTY(EditAnywhere)
	float HittedTime = 0.f;

public:

	FORCEINLINE float GetAO_Yaw() { return AO_Yaw; }
	FORCEINLINE float GetAO_Pitch() { return AO_Pitch; }
	FORCEINLINE ETurnInPlace GetTurningInPlace() { return TurnInPlace; }
	FORCEINLINE bool GetbRotateRootBone() { return bRotateRootBone; }
	FORCEINLINE AWeapon* GetDefaultWeapon() { return DefaultWeapon; }
	FORCEINLINE FVector GetHitTarget() { return HitTarget; }
	FORCEINLINE EActionState GetActionState() { return ActionState; }
	FORCEINLINE AAmmoPickUp* GetAmmoPickUp() { return AmmoPickup; }
	FORCEINLINE EKeyState GetKeyState() { return KeyState; }
	void SetFlashLightState(EFlashLightState State) { FlashLightState = State; }
	void SetEquippedFlashLight(AFlashLight* FlashLight) { EquippedFlashLight = FlashLight; }
	void SetKeyState(EKeyState State) { KeyState = State; }
};