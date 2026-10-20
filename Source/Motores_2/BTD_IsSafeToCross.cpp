#include "BTD_IsSafeToCross.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Crosswalk.h"
#include "PedestrianTrafficLight.h"

UBTD_IsSafeToCross::UBTD_IsSafeToCross()
{
	NodeName = "Is Safe To Cross?";
}

bool UBTD_IsSafeToCross::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return false;

	// Extraemos el cruce usando la llave del Blackboard
	ACrosswalk* Crosswalk = Cast<ACrosswalk>(BB->GetValueAsObject(CrosswalkKey.SelectedKeyName));

	// Si no hay cruce guardado o no tiene un semáforo asignado en el nivel, no es seguro cruzar
	if (!Crosswalk || !Crosswalk->LinkedTrafficLight)
	{
		return false;
	}

	// Devuelve verdadero SOLO si el estado del semáforo es Walk (Verde)
	return Crosswalk->LinkedTrafficLight->CurrentState == EPedestrianLightState::Walk;
}