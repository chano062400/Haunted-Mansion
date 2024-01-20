// Fill out your copyright notice in the Description page of Project Settings.


#include "HauntedMension/Ai/BTDecorator_CanAttack.h"
#include "SevarogAIController.h"
#include "Kismet/GamePlayStatics.h"
#include "HauntedMension/Character/Phase.h"
#include "Sevarog.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CanAttack::UBTDecorator_CanAttack()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	
	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
		return false;

	auto Target = Cast<APhase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	if (Target == nullptr || Target->ActorHasTag(FName("Dead")))
		return false;

	return bResult && Target->GetDistanceTo(CurrentPawn) <= 200.0f;
}
