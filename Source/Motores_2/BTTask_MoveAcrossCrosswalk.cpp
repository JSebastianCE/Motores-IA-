#include "BTTask_MoveAcrossCrosswalk.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PedestrianCharacter.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_MoveAcrossCrosswalk::UBTTask_MoveAcrossCrosswalk()
{
	NodeName = "Setup Crosswalk Movement";
}

EBTNodeResult::Type UBTTask_MoveAcrossCrosswalk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APedestrianCharacter* Pedestrian = Cast<APedestrianCharacter>(OwnerComp.GetAIOwner() ? OwnerComp.GetAIOwner()->GetPawn() : nullptr);
	if (!Pedestrian) return EBTNodeResult::Failed;

	// Aplicar la velocidad de cruce
	Pedestrian->GetCharacterMovement()->MaxWalkSpeed = Pedestrian->CrossingSpeed;

	return EBTNodeResult::Succeeded;
}