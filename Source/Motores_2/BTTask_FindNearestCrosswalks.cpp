#include "BTTask_FindNearestCrosswalks.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Crosswalk.h"
#include "AIController.h"

UBTTask_FindNearestCrosswalks::UBTTask_FindNearestCrosswalks()
{
	NodeName = "Find Nearest Crosswalk";
}

EBTNodeResult::Type UBTTask_FindNearestCrosswalks::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner() ? OwnerComp.GetAIOwner()->GetPawn() : nullptr;
	if (!ControllingPawn) return EBTNodeResult::Failed;

	TArray<AActor*> AllCrosswalks;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACrosswalk::StaticClass(), AllCrosswalks);

	ACrosswalk* NearestCrosswalk = nullptr;
	float MinDistanceSq = UE_MAX_FLT;
	FVector PawnLoc = ControllingPawn->GetActorLocation();

	for (AActor* Actor : AllCrosswalks)
	{
		ACrosswalk* Crosswalk = Cast<ACrosswalk>(Actor);
		if (!Crosswalk) continue;

		float DistSq = FVector::DistSquared(PawnLoc, Crosswalk->GetActorLocation());
		if (DistSq < MinDistanceSq)
		{
			MinDistanceSq = DistSq;
			NearestCrosswalk = Crosswalk;
		}
	}

	if (NearestCrosswalk)
	{
		UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
		BB->SetValueAsObject(CrosswalkKey.SelectedKeyName, NearestCrosswalk);

		// Obtener la ubicación de la zona A y B
		FVector ZoneALoc = NearestCrosswalk->WaitingZoneSideA->GetComponentLocation();
		FVector ZoneBLoc = NearestCrosswalk->WaitingZoneSideB->GetComponentLocation();

		// Elegir la zona que esté más cerca del peatón
		float DistA = FVector::DistSquared(PawnLoc, ZoneALoc);
		float DistB = FVector::DistSquared(PawnLoc, ZoneBLoc);
		FVector TargetLoc = (DistA < DistB) ? ZoneALoc : ZoneBLoc;

		// Guardar como destino
		BB->SetValueAsVector(FName("TargetDestination"), TargetLoc);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}