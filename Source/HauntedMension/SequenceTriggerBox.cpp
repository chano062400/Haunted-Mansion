#include "HauntedMension/SequenceTriggerBox.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "HauntedMension/Ai/SkeletonWarrior/SkeletonWarrior.h"
#include "HauntedMension/Ai/SkeletonWarrior/SkeletonWarriorAIController.h"
#include "HauntedMension/Interact/PickUp/FlashLight.h"
#include "HauntedMension/Character/Phase.h"

ASequenceTriggerBox::ASequenceTriggerBox()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

void ASequenceTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASequenceTriggerBox::BeginOverlap);

	if (SequenceSkeleton1 && SequenceSkeleton2 && PlaySkeleton1 && PlaySkeleton2 && PlaySkeleton3)
	{
		UGameplayStatics::GetActorOfClass(GetWorld(), PlaySkeleton1)->SetActorHiddenInGame(true);
		UGameplayStatics::GetActorOfClass(GetWorld(), PlaySkeleton2)->SetActorHiddenInGame(true);
		UGameplayStatics::GetActorOfClass(GetWorld(), PlaySkeleton3)->SetActorHiddenInGame(true);
	}
}

void ASequenceTriggerBox::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	ALevelSequenceActor* LevelSequenceActor;
	FMovieSceneSequencePlaybackSettings  PlayBackSettings;
	PlayBackSettings.bDisableLookAtInput = true;
	PlayBackSettings.bDisableMovementInput = true;
	PlayBackSettings.bHideHud = true;
	PlayBackSettings.bHidePlayer = true;

	APhase* Phase = Cast<APhase>(UGameplayStatics::GetActorOfClass(GetWorld(), PlayerCharacter));
	if (Phase && Phase->EquippedFlashLight)
	{
		Phase->EquippedFlashLight->TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		if (Phase->EquippedFlashLight->bLightOn == true)
		{
			Phase->FlashOnOffPressed();
		}
	}

	LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, PlayBackSettings, LevelSequenceActor);
	LevelSequencePlayer->OnFinished.AddDynamic(this, &ASequenceTriggerBox::ShowSKeleton);
	LevelSequencePlayer->Play();

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASequenceTriggerBox::ShowSKeleton()
{
	if (SequenceSkeleton1 && SequenceSkeleton2 && PlaySkeleton1 && PlaySkeleton2 && PlaySkeleton3)
	{
		UGameplayStatics::GetActorOfClass(GetWorld(), PlaySkeleton1)->SetActorHiddenInGame(false);
		Cast<ASkeletonWarrior>(UGameplayStatics::GetActorOfClass(GetWorld(), PlaySkeleton1))->InitializeAIComponents();
		UGameplayStatics::GetActorOfClass(GetWorld(), PlaySkeleton2)->SetActorHiddenInGame(false);
		Cast<ASkeletonWarrior>(UGameplayStatics::GetActorOfClass(GetWorld(), PlaySkeleton2))->InitializeAIComponents();
		UGameplayStatics::GetActorOfClass(GetWorld(), PlaySkeleton3)->SetActorHiddenInGame(false);
		Cast<ASkeletonWarrior>(UGameplayStatics::GetActorOfClass(GetWorld(), PlaySkeleton3))->InitializeAIComponents();

		UGameplayStatics::GetActorOfClass(GetWorld(), SequenceSkeleton1)->Destroy();
		UGameplayStatics::GetActorOfClass(GetWorld(), SequenceSkeleton2)->Destroy();
	}

	APhase* Phase = Cast<APhase>(UGameplayStatics::GetActorOfClass(GetWorld(), PlayerCharacter));
	if (Phase && Phase->EquippedFlashLight)
	{
		Phase->EquippedFlashLight->TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

}

void ASequenceTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}