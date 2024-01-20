#pragma once

#include "CoreMinimal.h"
#include "HauntedMension/Interact/Interact.h"
#include "Components/TimeLineComponent.h"
#include "Drawer.generated.h"

class USoundBase;

UCLASS()
class HAUNTEDMENSION_API ADrawer : public AInteract
{
	GENERATED_BODY()

public:

	ADrawer();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void Interact();

protected:

	UFUNCTION()
	void DrawerMove(float DeltaTime);

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Handle1;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Handle1_2;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> DrawerSound;

};