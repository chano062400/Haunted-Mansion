#include "HauntedMension/Interact/Drawer.h"
#include "Components/TimeLineComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ADrawer::ADrawer()
{
	PrimaryActorTick.bCanEverTick = true;

	Handle1 = CreateDefaultSubobject<UStaticMeshComponent>("Handle1_1");
	Handle1->SetupAttachment(Mesh);

	Handle1_2 = CreateDefaultSubobject<UStaticMeshComponent>("Handle1_2");
	Handle1_2->SetupAttachment(Mesh);
}

void ADrawer::BeginPlay()
{
	Super::BeginPlay();

	if (InteractCurve)
	{
		TimelineUpdate.BindDynamic(this, &ADrawer::DrawerMove);

		Timeline->AddInterpFloat(InteractCurve, TimelineUpdate);
	}
}

void ADrawer::Interact()
{
	Timeline->PlayFromStart();
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ShowInteractWidget(false);

	UGameplayStatics::PlaySoundAtLocation(this, DrawerSound, GetActorLocation());
}

void ADrawer::DrawerMove(float DeltaTime)
{
	FVector Location(GetActorLocation().X, GetActorLocation().Y + MoveY * DeltaTime, GetActorLocation().Z);

	SetActorRelativeLocation(Location);
}

void ADrawer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}