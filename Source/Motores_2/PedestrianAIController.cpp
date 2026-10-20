#include "PedestrianAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void APedestrianAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
		PedestrianBlackboard = GetBlackboardComponent();
	}
}

void APedestrianAIController::SetDestination(AActor* NewDestination)
{
	// Buscamos el Blackboard dinámicamente si la variable aún no está guardada
	UBlackboardComponent* BB = PedestrianBlackboard ? PedestrianBlackboard : GetBlackboardComponent();

	if (BB && NewDestination)
	{
		BB->SetValueAsObject(FName("TargetDestination"), NewDestination);
	}
}

AActor* APedestrianAIController::GetDestination() const
{
	// Agregamos 'const' a la variable local
	const UBlackboardComponent* BB = PedestrianBlackboard ? PedestrianBlackboard : GetBlackboardComponent();
	if (BB)
	{
		return Cast<AActor>(BB->GetValueAsObject(FName("TargetDestination")));
	}
	return nullptr;
}