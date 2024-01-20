#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HauntedMension/Interfaces/HitInterface.h"
#include "Components/TimelineComponent.h"
#include "SkeletonWarrior.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEnded);

class UAttributeComponent;
class UPawnSensingComponent;
class UBehaviorTree;
class USphereComponent;
class UMotionWarpingComponent;
class ASkeletonWarriorAIController;

UCLASS()
class HAUNTEDMENSION_API ASkeletonWarrior : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:

	ASkeletonWarrior();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void StartDissolve();

	UFUNCTION()
	void StopDissolve();

	UFUNCTION()
	void UpdateDissolve(float DeltaTime);

	UPROPERTY(EditAnywhere)
	bool IsStanding = false;

	void Attack();

	FOnAttackEnded OnAttackEnded;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USphereComponent* RightHandSphere;

	UFUNCTION(BlueprintCallable)
	void AttackTrace();

	TArray<AActor*> ActorsToIgnore;

	UPROPERTY()
	ASkeletonWarriorAIController* AIController;

	void InitializeAIComponents();

protected:

	virtual void BeginPlay() override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;;

	UFUNCTION()
	void UpdateDie(float DeltaTime);

	void Die();

	UFUNCTION()
	void DissolveDie();

	UPROPERTY(VisibleAnywhere)
	bool IsDissolving = false;

	UPROPERTY(VisibleAnywhere)
	bool IsDying = false;

	UPROPERTY(EditAnywhere)
	float TraceDistance = 100.f;

	UPROPERTY(EditAnywhere)
	float TraceRadius = 50.f;

	UPROPERTY(EditAnywhere)
	float Damage = 30.f;

	UPROPERTY(EditAnywhere)
	bool ShowDebugBox = false;

	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* ScreamMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* DieMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* StandUpMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* AttackMontage;

	/* Dissolve Effect */

	UPROPERTY(VisibleAnywhere, Category = "Dissolve")
	UTimelineComponent* DissolveTimeline;

	FOnTimelineFloat DissolveTimelineUpdate;

	FOnTimelineEvent DissolveTimelineFinished;

	UPROPERTY(EditAnywhere, Category = "Dissolve")
	UCurveFloat* DissolveCurve;

	UPROPERTY(VisibleAnywhere, Category = "Dissolve")
	UMaterialInstanceDynamic* DynamicDissolveMaterialInstance;

	UPROPERTY(EditAnywhere, Category = "Dissolve")
	UMaterialInstance* DissolveMateialInstance;

	/* Die Effect */

	UPROPERTY(VisibleAnywhere, Category = "Die")
	UTimelineComponent* DieTimeline;

	FOnTimelineFloat DieTimelineUpdate;

	FOnTimelineEvent DieTimelineFinished;

	UPROPERTY(EditAnywhere, Category = "Die")
	UCurveFloat* DieCurve;

	UPROPERTY(VisibleAnywhere, Category = "Die")
	UMaterialInstanceDynamic* DynamicDieMaterialInstance;

	UPROPERTY(EditAnywhere, Category = "Die")
	UMaterialInstance* DieMateialInstance;

	FTimerHandle ScreamTimerHandle;

	FTimerHandle DieTimerHandle;

	/* Basic Properites */

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* Attribute;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsAttacking = false;

	/* AI */

	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

	/* Motion Warping */

	UFUNCTION(BlueprintCallable)
	FVector GetTargetRotation();

	UFUNCTION(BlueprintCallable)
	FVector GetTargetLocation();

	UPROPERTY(EditAnywhere, Category = "Motion Warping")
	float WarpDistance = 80.f;

	UPROPERTY(EditAnywhere, Category = "Motion Warping")
	float DistanceToTarget = 150.f;

public:

	FORCEINLINE bool SetIsStanding(bool bStanding) { return IsStanding = bStanding; }
	FORCEINLINE bool GetIsStanding() { return IsStanding; }
};