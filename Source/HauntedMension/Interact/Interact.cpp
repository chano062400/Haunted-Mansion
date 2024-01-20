#include "Interact.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "HauntedMension/Interfaces/InteractInterface.h"
#include "HauntedMension/Character/Phase.h"
#include "Components/WidgetComponent.h"
#include "HauntedMension/Character/Phase.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h"

AInteract::AInteract()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	InteractWidget->SetupAttachment(Mesh);

	TargetCamera = CreateDefaultSubobject<UCameraComponent>("Target Camera");
	TargetCamera->SetupAttachment(Mesh);

	Timeline = CreateDefaultSubobject<UTimelineComponent>("Timeline");

}

void AInteract::BeginPlay()
{
	Super::BeginPlay();

	if (InteractWidget) InteractWidget->SetVisibility(false);
}

//void AInteract::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	APhase* Character = Cast<APhase>(OtherActor);
//	
//	if (Character && InteractWidget)
//	{
//		Character->SetOverlappingInteractitem(this);
//		ShowInteractWidget(true);
//	}
//}
//
//void AInteract::OnEndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	APhase* Character = Cast<APhase>(OtherActor);
//
//	if (Character && InteractWidget)
//	{
//		Character->SetOverlappingInteractitem(nullptr);
//		ShowInteractWidget(false);
//	}
//}

void AInteract::Interact()
{

}

//void AInteract::EnableCustomDepth(bool Enable)
//{
//	Mesh->SetRenderCustomDepth(Enable);
//}

void AInteract::ShowInteractWidget(bool bShowWidget)
{
	if (InteractWidget)
	{
		InteractWidget->SetVisibility(bShowWidget);
	}
}

void AInteract::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}