#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PedestrianSpawnPoint.generated.h"

// Le decimos al compilador que esta clase existe para poder usarla en las variables
class APedestrianCharacter;

UCLASS()
class MOTORES_2_API APedestrianSpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	APedestrianSpawnPoint();

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int32 MaxSpawnCount = 10;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float SpawnRadius = 150.0f;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<AActor*> PossibleDestinations;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<APedestrianCharacter> PedestrianClass;
};