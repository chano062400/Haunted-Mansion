#pragma once

#include "CoreMinimal.h"
#include "HauntedMension/Interact/Interact.h"
#include "Components/TimeLineComponent.h"
#include "Door.generated.h"

class UCurveFloat;
class USoundBase;
/**
 *
 */
UCLASS()
class HAUNTEDMENSION_API ADoor : public AInteract
{

	GENERATED_BODY()

public:

	ADoor();

	virtual void Interact() override;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ChangeState();

	UFUNCTION()
	void InteractDoor(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> Door;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> DoorFrame;

	// SafeHandle이 Interact하고나서 Interact할 SafeDoor를 설정.
	UPROPERTY(EditAnywhere, Category = "Door")
	TSubclassOf<AActor> SafeDoor;

	UPROPERTY(EditAnywhere, Category = "Door")
	FString DoorText;

	UPROPERTY(EditAnywhere, Category = "Door")
	TObjectPtr<USoundBase> DoorSound;

	UPROPERTY(EditAnywhere, Category = "Door") // 문이 열린 상태인지 닫힌 상태인지 알려주는 변수.
		bool IsOpened = false;

	UPROPERTY(EditAnywhere, Category = "Door") // 한번 열면 열린 채로 두기위한 변수
		bool SetOpen = false;

	UPROPERTY(VisibleAnywhere, Category = "Door") // 문이 열리는 동안 Interact못하도록 하는 변수
		bool IsOpening = false;

	UPROPERTY(EditAnywhere, Category = "Door")
	bool IsSafeHandle = false;

	FTimerHandle CameraChangeTimer;

};