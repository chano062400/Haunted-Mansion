// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HauntedMension/Interact/Interact.h"
#include "Components/TimeLineComponent.h"
#include "Book.generated.h"

class UAnimMontage;
class UCurveFloat;
class USoundBase;
class UCameraComponent;
class ULevelSequencePlayer;
class ULevelSequence;

/**
 *
 */
UCLASS()
class HAUNTEDMENSION_API ABook : public AInteract
{
	GENERATED_BODY()

public:

	ABook();

	virtual void Interact() override;

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void StoneStatueInteract();

	UPROPERTY(EditAnywhere, Category = "Sequence")
	TObjectPtr<ULevelSequencePlayer> LevelSequencePlayer;

	UPROPERTY(EditAnywhere, Category = "Sequence")
	TObjectPtr<ULevelSequence> LevelSequence;

	UPROPERTY(EditAnywhere, Category = "Sequence")
	TSubclassOf<AActor> SequencePhase;

};