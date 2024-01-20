#pragma once

#include "CoreMinimal.h"
#include "HauntedMension/Interact/Interact.h"
#include "HintPage.generated.h"

class UCameraComponent;

/**
 *
 */
UCLASS()
class HAUNTEDMENSION_API AHintPage : public AInteract
{
	GENERATED_BODY()

public:

	AHintPage();

	virtual void Interact() override;

protected:

	FTimerHandle CameraHandle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HintPageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 PageNumber = 1;
};