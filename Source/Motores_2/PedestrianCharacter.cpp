#include "PedestrianCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Constructor
APedestrianCharacter::APedestrianCharacter()
{
	// Optimización: Desactivamos el Tick porque la IA se controlará por el Behavior Tree
	PrimaryActorTick.bCanEverTick = false;

	// Configuración de movimiento base
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// Configuración de evasión para que no se empujen entre ellos
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 80.0f;

	// Obligar al NavMesh a generar datos de aceleración para el AnimBP
	GetCharacterMovement()->bRequestedMoveUseAcceleration = true;
}

void APedestrianCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Asegurarnos de que la velocidad inicial sea la de caminata
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}