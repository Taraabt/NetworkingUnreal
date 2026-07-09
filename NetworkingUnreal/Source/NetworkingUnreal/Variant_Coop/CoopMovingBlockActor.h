#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoopMovingBlockActor.generated.h"

class UStaticMeshComponent;
class UMaterialInterface;
class FLifetimeProperty;


UCLASS(Abstract)
class ACoopMovingBlockActor : public AActor
{
	GENERATED_BODY()

public:

	ACoopMovingBlockActor();


	void SetOpen(bool bNewOpen);

	UFUNCTION(BlueprintPure, Category="Movement")
	bool IsOpen() const { return bOpen; }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	FVector OpenOffset = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, Category="Movement", meta = (ClampMin = 0.0f, Units = "cm/s"))
	float MoveSpeed = 220.0f;

	UPROPERTY(EditDefaultsOnly, Category="Appearance")
	TObjectPtr<UMaterialInterface> BaseMaterial;

	UPROPERTY(EditDefaultsOnly, Category="Appearance")
	FLinearColor TintColor = FLinearColor::White;

	UPROPERTY(ReplicatedUsing = OnRep_OpenState)
	bool bOpen = false;

	FVector ClosedLocation = FVector::ZeroVector;

	FVector OpenLocation = FVector::ZeroVector;

	UFUNCTION()
	void OnRep_OpenState();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
