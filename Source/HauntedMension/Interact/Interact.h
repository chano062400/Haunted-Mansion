#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HauntedMension/Interfaces/InteractInterface.h"
#include "Components/TimelineComponent.h"
#include "Interact.generated.h"

class USceneComponent;
class UWidgetComponent;
class UCameraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractEnded);

UCLASS()
class HAUNTEDMENSION_API AInteract : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	AInteract();

	virtual void Tick(float DeltaTime) override;

	virtual void ShowInteractWidget(bool bShowWidget);

	/* 기존 SICKAMANSION 맵의 PostProcessVolume의 Material과 충돌이 나서 OutLIne 기능은 빠짐.
	void EnableCustomDepth(bool Enable); */

	/* SetOverlapping 방식을 기존 SphereOverlap 방식에서 LineTrace방식으로 교체하여서 빠짐.
	virtual void  OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void  OnEndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex); */

	// Interact Item의 CameraComponent. 카메라 시점 변경 때 쓰임.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> TargetCamera;

	// Interact가 끝났음을 알려주는 Delegate
	FOnInteractEnded OnInteractEnded;

protected:

	virtual void BeginPlay() override;

	virtual void Interact() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> InteractWidget;

	// TimelineComponent

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTimelineComponent> Timeline;

	FOnTimelineFloat TimelineUpdate;

	FOnTimelineEvent TimelineFinish;

	UPROPERTY(EditAnywhere, Category = "Interact")
	TObjectPtr<UCurveFloat> InteractCurve;

	// Interact 

	UPROPERTY(EditAnywhere)
	float WaitTime = 2.f;

	UPROPERTY(EditAnywhere, Category = "Interact")
	float CameraBlendTime = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Interact")
	float MoveX = 0.f;

	UPROPERTY(EditAnywhere, Category = "Interact")
	float MoveY = 0.f;

	UPROPERTY(EditAnywhere, Category = "Interact")
	float MoveZ = 0.f;

	UPROPERTY(EditAnywhere, Category = "Interact")
	float RotatePitch = 0.f;

	UPROPERTY(EditAnywhere, Category = "Interact")
	float RotateYaw = 0.f;

	UPROPERTY(EditAnywhere, Category = "Interact")
	float RotateRoll = 0.f;

public:

	FORCEINLINE UStaticMeshComponent* GetInteractMesh() { return Mesh; }
};