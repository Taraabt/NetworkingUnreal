#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoopDoorButtonVolume.generated.h"

class ACharacter;
class ACoopSlidingDoor;

class UBoxComponent;
class UStaticMeshComponent;
class UTextRenderComponent;
class UPrimitiveComponent;

struct FHitResult;

UCLASS()
class ACoopDoorButtonVolume : public AActor
{
	GENERATED_BODY()

public:

	ACoopDoorButtonVolume();

	void SetTargetDoor(ACoopSlidingDoor* InDoor);

protected:

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components",
		meta = (AllowPrivateAccess = "true")
	)
	TObjectPtr<UBoxComponent> TriggerBox;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components",
		meta = (AllowPrivateAccess = "true")
	)
	TObjectPtr<UStaticMeshComponent> VisualButton;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components",
		meta = (AllowPrivateAccess = "true")
	)
	TObjectPtr<UTextRenderComponent> InstructionText;

	UPROPERTY(
		EditInstanceOnly,
		BlueprintReadOnly,
		Category = "Puzzle"
	)
	TObjectPtr<ACoopSlidingDoor> TargetDoor;

	TSet<TWeakObjectPtr<ACharacter>> TouchingPlayers;

	UFUNCTION()
	void OnTriggerBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnTriggerEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
};