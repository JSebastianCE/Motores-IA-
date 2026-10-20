#include "PedestrianSimulationManager.h"
#include "PedestrianSpawnPoint.h"
#include "PedestrianCharacter.h"
#include "PedestrianAIController.h"
#include "Math/UnrealMathUtility.h"

APedestrianSimulationManager::APedestrianSimulationManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APedestrianSimulationManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnInitialPedestrians();
}

void APedestrianSimulationManager::SpawnInitialPedestrians()
{
	// Si no pusimos Spawn Points en el mapa, no hacemos nada
	if (SpawnPoints.Num() == 0)
	{
		return;
	}

	for (int32 i = 0; i < TotalPedestriansToSpawn; ++i)
	{
		// Repartimos los peatones entre los puntos de aparición disponibles
		APedestrianSpawnPoint* SpawnPoint = SpawnPoints[i % SpawnPoints.Num()];

		if (!SpawnPoint || !SpawnPoint->PedestrianClass)
		{
			continue;
		}

		// Calculamos una posición aleatoria alrededor del punto para que no salgan encimados
		FVector Origin = SpawnPoint->GetActorLocation();
		FVector RandomOffset = FMath::VRand();
		RandomOffset.Z = 0.0f;
		RandomOffset = RandomOffset.GetSafeNormal() * FMath::RandRange(0.0f, SpawnPoint->SpawnRadius);
		FVector SpawnLocation = Origin + RandomOffset;

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// Spawnear al peatón
		APedestrianCharacter* Pedestrian = GetWorld()->SpawnActor<APedestrianCharacter>(
			SpawnPoint->PedestrianClass,
			SpawnLocation,
			SpawnPoint->GetActorRotation(),
			Params
		);

		// Si se creó con éxito, le asignamos su destino inicial
		if (Pedestrian)
		{
			AActor* Destination = GetRandomDestination();
			APedestrianAIController* AIController = Cast<APedestrianAIController>(Pedestrian->GetController());

			if (AIController && Destination)
			{
				AIController->SetDestination(Destination);
			}
		}
	}
}

AActor* APedestrianSimulationManager::GetRandomDestination() const
{
	if (GlobalDestinations.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, GlobalDestinations.Num() - 1);
		return GlobalDestinations[RandomIndex];
	}
	return nullptr;
}