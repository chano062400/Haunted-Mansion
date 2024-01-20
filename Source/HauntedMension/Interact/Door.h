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

	// SafeHandle�� Interact�ϰ��� Interact�� SafeDoor�� ����.
	UPROPERTY(EditAnywhere, Category = "Door")
	TSubclassOf<AActor> SafeDoor;

	UPROPERTY(EditAnywhere, Category = "Door")
	FString DoorText;

	UPROPERTY(EditAnywhere, Category = "Door")
	TObjectPtr<USoundBase> DoorSound;

	UPROPERTY(EditAnywhere, Category = "Door") // ���� ���� �������� ���� �������� �˷��ִ� ����.
		bool IsOpened = false;

	UPROPERTY(EditAnywhere, Category = "Door") // �ѹ� ���� ���� ä�� �α����� ����
		bool SetOpen = false;

	UPROPERTY(VisibleAnywhere, Category = "Door") // ���� ������ ���� Interact���ϵ��� �ϴ� ����
		bool IsOpening = false;

	UPROPERTY(EditAnywhere, Category = "Door")
	bool IsSafeHandle = false;

	FTimerHandle CameraChangeTimer;

};