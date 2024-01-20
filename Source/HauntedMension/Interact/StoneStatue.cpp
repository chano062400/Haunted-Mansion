#include "StoneStatue.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SplineComponent.h"

AStoneStatue::AStoneStatue()
{
	MoveEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>("Move Effect");
	MoveEffectComponent->SetupAttachment(Mesh);
}

void AStoneStatue::BeginPlay()
{
	Super::BeginPlay();

	MoveEffectComponent->DeactivateSystem();

	if (InteractCurve)
	{
		TimelineUpdate.BindDynamic(this, &AStoneStatue::StatueMove);
		Timeline->AddInterpFloat(InteractCurve, TimelineUpdate);
		TimelineFinish.BindDynamic(this, &AStoneStatue::DestroyMoveEffect);
		Timeline->SetTimelineFinishedFunc(TimelineFinish);
	}

}

void AStoneStatue::Interact()
{
	if (MoveSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, MoveSound, GetActorLocation(), GetActorRotation());
	}

	SpawnMoveEffect();

	PlayCameraShake();

	Timeline->PlayFromStart();
}

void AStoneStatue::StatueMove(float DeltaTime)
{
	FVector Location(GetActorLocation().X + MoveX * DeltaTime, GetActorLocation().Y + MoveY * DeltaTime, GetActorLocation().Z + MoveZ * DeltaTime);

	SetActorRelativeLocation(Location);
}

void AStoneStatue::PlayCameraShake()
{
	if (IsValid(CameraShake))
	{
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CameraShake);
	}
}

void AStoneStatue::SpawnMoveEffect()
{
	if (MoveEffectComponent) MoveEffectComponent->ActivateSystem();
}

void AStoneStatue::DestroyMoveEffect()
{
	if (MoveEffectComponent) MoveEffectComponent->DestroyComponent();
}

void AStoneStatue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
