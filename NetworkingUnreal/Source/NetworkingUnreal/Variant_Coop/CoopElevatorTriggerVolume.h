#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoopElevatorTriggerVolume.generated.h"

class ACharacter;
class ACoopElevatorPlatform;
class UBoxComponent;
class UStaticMeshComponent;
class UTextRenderComponent;
class UPrimitiveComponent;

struct FHitResult;

UCLASS()
class ACoopElevatorTriggerVolume : public AActor
{
	GENERATED_BODY()

public:
	ACoopElevatorTriggerVolume();

	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	void SetPlatform(ACoopElevatorPlatform* InPlatform);

protected:
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components"
	)
	TObjectPtr<UBoxComponent> TriggerBox;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components"
	)
	TObjectPtr<UStaticMeshComponent> VisualPad;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components"
	)
	TObjectPtr<UTextRenderComponent> InstructionText;

	UPROPERTY(
		EditInstanceOnly,
		BlueprintReadOnly,
		Category = "Puzzle"
	)
	TObjectPtr<ACoopElevatorPlatform> TargetPlatform;

	TSet<TWeakObjectPtr<ACharacter>> OverlappingPlayers;

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

	void SyncPlatform();
};