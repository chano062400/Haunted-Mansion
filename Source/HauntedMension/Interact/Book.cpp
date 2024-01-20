#include "Book.h"
#include "HauntedMension/Character/Phase.h"
#include "HauntedMension/Interact/StoneStatue.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "HauntedMension/Controller/HMController.h"
#include "Camera/CameraComponent.h"
#include "HauntedMension/Weapon/Weapon.h"

ABook::ABook()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh->SetupAttachment(GetRootComponent());
}

void ABook::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetActorOfClass(GetWorld(), SequencePhase)->SetActorHiddenInGame(true);
}


void ABook::StoneStatueInteract()
{
	TArray<AActor*> StoneStatues;

	UGameplayStatics::GetActorOfClass(GetWorld(), SequencePhase)->Destroy();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStoneStatue::StaticClass(), StoneStatues); //StoneStatue클래스인 엑터들을 가져와 StoneStatues배열에 담아서 반환.
	for (auto statue : StoneStatues)
	{
		AStoneStatue* StoneStatue = Cast<AStoneStatue>(statue);
		if (StoneStatue)
		{
			StoneStatue->Interact();
		}
	}

	Destroy();

}

void ABook::Interact()
{

	ShowInteractWidget(false);

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (SequencePhase) UGameplayStatics::GetActorOfClass(GetWorld(), SequencePhase)->SetActorHiddenInGame(false);

	FMovieSceneSequencePlaybackSettings  PlayBackSettings;
	PlayBackSettings.bDisableLookAtInput = true;
	PlayBackSettings.bDisableMovementInput = true;
	PlayBackSettings.bHideHud = true;
	PlayBackSettings.bHidePlayer = true;

	ALevelSequenceActor* LevelSequenceActor;
	LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, PlayBackSettings, LevelSequenceActor);
	LevelSequencePlayer->OnFinished.AddDynamic(this, &ABook::StoneStatueInteract);
	LevelSequencePlayer->Play();

}

void ABook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}