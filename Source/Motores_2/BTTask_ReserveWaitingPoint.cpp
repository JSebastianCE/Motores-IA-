#include "BTTask_ReserveWaitingPoint.h"

UBTTask_ReserveWaitingPoint::UBTTask_ReserveWaitingPoint()
{
	NodeName = "Reserve Waiting Point (Obsoletazo)";
}

EBTNodeResult::Type UBTTask_ReserveWaitingPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Tarea reemplazada por los Triggers de colisión en ACrosswalk
	return EBTNodeResult::Succeeded;
}