#include "PedestrianSpawnPoint.h"

APedestrianSpawnPoint::APedestrianSpawnPoint()
{
	// Optimizamos apagando el Tick
	PrimaryActorTick.bCanEverTick = false;
}