// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "HauntedMension/Character/Phase.h"
#include "BTDecorator_CanAttack.generated.h"

/**
 * 
 */
UCLASS()
class HAUNTEDMENSION_API UBTDecorator_CanAttack : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_CanAttack();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
