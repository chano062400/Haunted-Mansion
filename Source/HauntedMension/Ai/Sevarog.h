// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "HauntedMension/HMTypes/HMTypes.h"
#include "HauntedMension/Interfaces/HitInterface.h"
#include "Sevarog.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);
DECLARE_MULTICAST_DELEGATE(FOnHitEnd);
DECLARE_MULTICAST_DELEGATE(FOnHitInfo);

UCLASS()
class HAUNTEDMENSION_API ASevarog : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASevarog();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpDown(float Value);
	void LeftRight(float Value);
	void Yaw(float Value);

	FOnAttackEnd OnAttackEnd;
	FOnHitEnd OnHitEnd;
	FOnHitInfo OnHitInfo;

	void Attack();
	void AttackCheck();
	void PlayerDieCheck();

	// ���� ���� üũ�� ���� �ൿ ����
	void Chase(AActor* Target);
	void Die();
	void StateRefresh();

	// ���¸ӽ��� AIController���� ó���Ѵ�.
	// ���ݻ��°� ����Ǹ� ��������Ʈ�� ���� �˸���.
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterruppted);
	void OnHitMontageEnded(UAnimMontage* Montage, bool bInterruppted);

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	
	UFUNCTION(BlueprintCallable)
	FVector GetPlayerRotation();

	UFUNCTION(BlueprintCallable)
	FVector GetPlayerLocation();

	UPROPERTY(EditAnywhere)
	float WarpDistance = 100.f;

	void PlayAttackMontage();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn)
	UAnimMontage* AttackMontage;

private:
	// ���� ���¸� �˱� ���� �÷���
	UPROPERTY()
	bool IsAttacking = false;

	UPROPERTY()
	bool IsHit = false;

	UPROPERTY()
	float AttackDist = 150.0f;

	UPROPERTY()
	float SearchRange = 500.0f;

	UPROPERTY()
	float SearchInterval = 3.0f;

	UPROPERTY()
	class USevarogAnimInstance* AnimInstance;

	UPROPERTY()
	int32 AttackIndex = 0;

	UPROPERTY(VisibleAnywhere)
	class UAttributeComponent* Stat;

public:
	UPROPERTY(VisibleAnywhere, Category=Awareness)
	UPawnSensingComponent* PawnSensor;

	UPROPERTY()
	float UpDownValue;

	UPROPERTY()
	float LeftRightValue;

	UPROPERTY(VisibleAnywhere)
	ESevarogState State;

	UPROPERTY(VisibleAnywhere)
	AActor* Player;

	UPROPERTY(VisibleAnywhere)
	AActor* PatrolTarget;

	UPROPERTY(VisibleAnywhere)
	AAIController* EnemyController;

	UPROPERTY(EditAnywhere)
	 class UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere)
	UAnimMontage* HitMontage;
};
