#include "PedestrianWaitingPoint.h"

APedestrianWaitingPoint::APedestrianWaitingPoint()
{
	PrimaryActorTick.bCanEverTick = false;
	bIsOccupied = false;
}