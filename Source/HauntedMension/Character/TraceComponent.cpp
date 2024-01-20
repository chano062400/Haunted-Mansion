#include "HauntedMension/Character/TraceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HauntedMension/Interact/Interact.h"
#include "HauntedMension/Character/Phase.h"
#include "Components/SphereComponent.h"

UTraceComponent::UTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickInterval(0.03f);
}


void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	check(CameraManager);

	FHitResult TraceHitResult;
	TArray<AActor*> ActorsToIgnore;
	FVector Start = CameraManager->GetCameraLocation();
	FVector End = Start + CameraManager->GetActorForwardVector() * TraceLength;
	UKismetSystemLibrary::LineTraceSingle(
		this,
		Start,
		End,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		bShowDebug == true ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		TraceHitResult,
		true
	);

	AActor* InteractActor = TraceHitResult.GetActor();
	if (InteractActor)
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *InteractActor->GetName());
	}
	if (InteractActor == nullptr) return;

	PrevInteractItem = ThisInteractItem;
	ThisInteractItem = Cast<AInteract>(TraceHitResult.GetActor());
	APhase* Phase = Cast<APhase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (PrevInteractItem == nullptr)
	{
		if (ThisInteractItem) //2번 케이스
		{
			ThisInteractItem->ShowInteractWidget(true);
			Phase->SetOverlappingInteractitem(ThisInteractItem);
		}
		else // 1번 케이스
		{
			Phase->SetOverlappingInteractitem(nullptr);
		}
	}
	else
	{
		if (ThisInteractItem != nullptr)
		{
			if (ThisInteractItem != PrevInteractItem) //4번 케이스
			{
				PrevInteractItem->ShowInteractWidget(false);
				ThisInteractItem->ShowInteractWidget(true);
				Phase->SetOverlappingInteractitem(ThisInteractItem);
			}
		}
		else // 3번 케이스
		{
			PrevInteractItem->ShowInteractWidget(false);
			Phase->SetOverlappingInteractitem(nullptr);
		}
	}
}

