#include "FlashLight.h"
#include "Components/SpotLightComponent.h"
#include "Components/SphereComponent.h"
#include "HauntedMension/Character/Phase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "HauntedMension/Ai/SkeletonWarrior/SkeletonWarrior.h"
#include "HauntedMension/HUD/HMHUD.h"
#include "HauntedMension/HUD/HMOverlay.h"
#include "HauntedMension/Controller/HMController.h"

AFlashLight::AFlashLight()
{
	PrimaryActorTick.bCanEverTick = true;

	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light"));
	Light->SetupAttachment(Mesh, FName("FlashSocket"));

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox->SetupAttachment(Mesh, FName("FlashSocekt"));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void AFlashLight::BeginPlay()
{
	Super::BeginPlay();

	Light->SetIntensity(InitialBrightness);

	if (TriggerBox)
	{
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFlashLight::TriggerBoxBeginOverlap);

		TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AFlashLight::TriggerBoxEndOverlap);
	}
}

void AFlashLight::SetLightOnOff(bool bLightOnOff)
{
	bLightOn = bLightOnOff;

	if (bLightOn)
	{
		Light->SetIntensity(OnBrightness);
	}
	else
	{
		Light->SetIntensity(InitialBrightness);
	}
}

void AFlashLight::Interact()
{
	APhase* Character = Cast<APhase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	AHMController* Controller = Cast<AHMController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (Character && Controller)
	{
		Controller->GetHUD<AHMHUD>()->HMOverlay->PlayPickUp(FText::FromString("+ "), FlashLightImage);
		Character->PlayPickUpMontage();
		Character->SetFlashLightState(EFlashLightState::EFS_EquippedFlashLight);
		Character->SetEquippedFlashLight(this);
	}
}

void AFlashLight::TriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASkeletonWarrior* SkeletonWarrior = Cast<ASkeletonWarrior>(OtherActor);
	if (SkeletonWarrior && bLightOn)
	{
		SkeletonWarrior->StartDissolve();
	}
}

void AFlashLight::TriggerBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ASkeletonWarrior* SkeletonWarrior = Cast<ASkeletonWarrior>(OtherActor);
	if (SkeletonWarrior && bLightOn)
	{
		SkeletonWarrior->StopDissolve();
	}
}

void AFlashLight::Equip(USceneComponent* Inparent, AActor* NewOwner, APawn* NewInstigator)
{
	SetOwner(NewOwner);

	SetInstigator(NewInstigator);

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

	Mesh->AttachToComponent(Inparent, AttachmentRules, FName("LeftHandSocket"));

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AFlashLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}