#pragma once

#include "CoreMinimal.h"
#include "HauntedMension/Interact/Interact.h"
#include "Components/TimeLineComponent.h"
#include "StoneStatue.generated.h"

class USoundBase;
class UParticleSystem;
class UParticleSystemComponent;

/**
 *
 */
UCLASS()
class HAUNTEDMENSION_API AStoneStatue : public AInteract
{
	GENERATED_BODY()

public:

	AStoneStatue();

	virtual void Interact() override;


	virtual void Tick(float DeltaTime) override;


protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void StatueMove(float DeltaTime);

	void PlayCameraShake();

	void SpawnMoveEffect();

	UFUNCTION()
	void DestroyMoveEffect();

private:

	UPROPERTY(EditAnywhere, Category = "Interact")
	TObjectPtr<USoundBase> MoveSound;

	FTimerHandle MoveEffectHandle;

	UPROPERTY(EditAnywhere, Category = "Interact")
	TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditAnywhere, Category = "Interact")
	TObjectPtr<UParticleSystemComponent> MoveEffectComponent;
};