#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PedestrianSimulationManager.generated.h"

class APedestrianSpawnPoint;

UCLASS()
class MOTORES_2_API APedestrianSimulationManager : public AActor
{
	GENERATED_BODY()

public:
	APedestrianSimulationManager();

	UPROPERTY(EditAnywhere, Category = "Simulation")
	int32 TotalPedestriansToSpawn = 30;

	// Lista de los puntos de aparición en el mapa
	UPROPERTY(EditAnywhere, Category = "Simulation")
	TArray<APedestrianSpawnPoint*> SpawnPoints;

	// Lista de destinos a los que los peatones pueden ir
	UPROPERTY(EditAnywhere, Category = "Simulation")
	TArray<AActor*> GlobalDestinations;

protected:
	virtual void BeginPlay() override;

	void SpawnInitialPedestrians();
	AActor* GetRandomDestination() const;
};