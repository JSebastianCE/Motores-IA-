#include "BTTask_ChooseRandomDestination.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Math/UnrealMathUtility.h" // Necesario para la probabilidad aleatoria

UBTTask_ChooseRandomDestination::UBTTask_ChooseRandomDestination()
{
  NodeName = "Choose Random Destination";
  SearchRadius = 1500.0f;
  CrossProbability = 0.3f; // 30% de probabilidad por defecto
}

EBTNodeResult::Type UBTTask_ChooseRandomDestination::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
  AAIController* AIController = OwnerComp.GetAIOwner();
  if (!AIController)
  {
    return EBTNodeResult::Failed;
  }

  APawn* AIPawn = AIController->GetPawn();
  if (!AIPawn)
  {
    return EBTNodeResult::Failed;
  }

  FVector Origin = AIPawn->GetActorLocation();
  UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(OwnerComp.GetWorld());

  if (NavSys)
  {
    FNavLocation RandomLocation;

    if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, RandomLocation))
    {
      UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

      // Asigna el nuevo destino aleatorio
      BlackboardComp->SetValueAsVector(GetSelectedBlackboardKey(), RandomLocation.Location);

      // Calcula si debe cruzar la calle (True o False basado en la probabilidad)
      bool bShouldCross = FMath::FRand() <= CrossProbability;

      // Actualiza la variable en el Blackboard
      BlackboardComp->SetValueAsBool(NeedsToCrossKey.SelectedKeyName, bShouldCross);

      return EBTNodeResult::Succeeded;
    }
  }

  return EBTNodeResult::Failed;
}