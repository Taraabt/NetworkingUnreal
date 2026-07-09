#include "Variant_Coop/CoopSlidingDoor.h"

#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "UObject/ConstructorHelpers.h"

ACoopSlidingDoor::ACoopSlidingDoor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorMesh(
		TEXT("/Game/LevelPrototyping/Interactable/Door/Assets/Meshes/SM_Door.SM_Door")
	);

	if (DoorMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(DoorMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> FlatMaterial(
		TEXT("/Game/LevelPrototyping/Materials/M_FlatCol.M_FlatCol")
	);

	if (FlatMaterial.Succeeded())
	{
		BaseMaterial = FlatMaterial.Object;
	}

	OpenOffset = FVector(0.0f, 360.0f, 0.0f);
	MoveSpeed = 260.0f;

	TintColor = FLinearColor(
		0.92f,
		0.90f,
		0.84f
	);
}