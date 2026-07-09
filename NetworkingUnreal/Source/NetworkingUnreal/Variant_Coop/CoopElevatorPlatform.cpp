#include "Variant_Coop/CoopElevatorPlatform.h"

#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "UObject/ConstructorHelpers.h"

ACoopElevatorPlatform::ACoopElevatorPlatform()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlatformMesh(
		TEXT("/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube")
	);

	if (PlatformMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(PlatformMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> FlatMaterial(
		TEXT("/Game/LevelPrototyping/Materials/M_FlatCol.M_FlatCol")
	);

	if (FlatMaterial.Succeeded())
	{
		BaseMaterial = FlatMaterial.Object;
	}

	OpenOffset = FVector(0.0f, 0.0f, 520.0f);

	MoveSpeed = 200.0f;

	TintColor = FLinearColor(0.90f, 0.82f, 0.62f);
}