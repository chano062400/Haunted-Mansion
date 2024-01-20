#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HauntedMension/Interact/Interact.h"
#include "HauntedMension/Interfaces/InteractInterface.h"
#include "FlashLight.generated.h"

class UImage;
class USpotLightComponent;
class UBoxComponent;

UCLASS()
class HAUNTEDMENSION_API AFlashLight : public AInteract
{
	GENERATED_BODY()

public:
	AFlashLight();

	virtual void Tick(float DeltaTime) override;

	void Equip(USceneComponent* Inparent, AActor* NewOwner, APawn* NewInstigator);

	void SetLightOnOff(bool bLightOnOff);

	virtual void Interact() override;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	bool bLightOn = false;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void TriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void TriggerBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	USpotLightComponent* Light;

	UPROPERTY(EditAnywhere)
	UTexture2D* FlashLightImage;

	float InitialBrightness = 0.f;

	float OnBrightness = 15000.f;

private:

public:

	FORCEINLINE bool GetbLightOn() { return bLightOn; }
};