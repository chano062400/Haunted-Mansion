#include "AmmoPickUp.h"
#include "HauntedMension/Character/Phase.h"
#include "HauntedMension/Weapon/Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "HauntedMension/Controller/HMController.h"
#include "HauntedMension/HUD/HMOverlay.h"
#include "HauntedMension/HUD/HMHUD.h"

AAmmoPickUp::AAmmoPickUp()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AAmmoPickUp::BeginPlay()
{
	Super::BeginPlay();
		
	/*Mesh->SetCustomDepthStencilValue(252);
	Mesh->MarkRenderStateDirty();
	EnableCustomDepth(true);*/
}

void AAmmoPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmoPickUp::Interact()
{
	APhase* Character = Cast<APhase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	AHMController* Controller = Cast<AHMController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (Character && Controller && Character->GetDefaultWeapon())
	{
		FString AmmountText = FString::Printf(TEXT("+ %d"), AmmountToPickUp);
		Controller->GetHUD<AHMHUD>()->HMOverlay->PlayPickUp(FText::FromString(AmmountText), AmmoImage); // UI에 설정한 AmmountToPickup의 수량과 AmmoImage을 띄움.
		Character->PlayPickUpMontage();
		Character->GetDefaultWeapon()->PickUpAmmo(AmmountToPickUp); // CarriedAmmo에 AmmountToPickup만큼 추가하고, UI 업데이트.
		this->Destroy();
	}
}

