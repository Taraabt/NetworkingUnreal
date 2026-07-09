// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoopWinPlateVolume.generated.h"

class ACharacter;
class ACoopPuzzleGameState;
class UBoxComponent;
class UStaticMeshComponent;
class UPrimitiveComponent;

struct FHitResult;

UCLASS()
class NETWORKINGUNREAL_API ACoopWinPlateVolume : public AActor
{
	GENERATED_BODY()

public:

	ACoopWinPlateVolume();


	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	void SetPlateIndex(int32 InPlateIndex);

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
		EditInstanceOnly,
		BlueprintReadOnly,
		Category = "Puzzle"
	)
	int32 PlateIndex = 0;


	TWeakObjectPtr<ACharacter> CurrentOccupant;

	UPROPERTY()
	TObjectPtr<ACoopPuzzleGameState> PuzzleGameState;

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


	void NotifyGameState();
};