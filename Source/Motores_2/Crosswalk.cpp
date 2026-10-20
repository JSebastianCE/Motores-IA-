#include "Crosswalk.h"
#include "PedestrianTrafficLight.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

ACrosswalk::ACrosswalk()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;

	WaitingZoneSideA = CreateDefaultSubobject<UBoxComponent>(TEXT("WaitingZoneSideA"));
	WaitingZoneSideA->SetupAttachment(RootComponent);

	WaitingZoneSideB = CreateDefaultSubobject<UBoxComponent>(TEXT("WaitingZoneSideB"));
	WaitingZoneSideB->SetupAttachment(RootComponent);

	ExitPointSideA = CreateDefaultSubobject<USceneComponent>(TEXT("ExitPointSideA"));
	ExitPointSideA->SetupAttachment(RootComponent);

	ExitPointSideB = CreateDefaultSubobject<USceneComponent>(TEXT("ExitPointSideB"));
	ExitPointSideB->SetupAttachment(RootComponent);
}

void ACrosswalk::BeginPlay()
{
	Super::BeginPlay();

	WaitingZoneSideA->OnComponentBeginOverlap.AddDynamic(this, &ACrosswalk::OnWaitingZoneBeginOverlap);
	WaitingZoneSideB->OnComponentBeginOverlap.AddDynamic(this, &ACrosswalk::OnWaitingZoneBeginOverlap);

	WaitingZoneSideA->OnComponentEndOverlap.AddDynamic(this, &ACrosswalk::OnWaitingZoneEndOverlap);
	WaitingZoneSideB->OnComponentEndOverlap.AddDynamic(this, &ACrosswalk::OnWaitingZoneEndOverlap);
}

void ACrosswalk::OnWaitingZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Pedestrian = Cast<ACharacter>(OtherActor);
	if (!Pedestrian) return;

	AAIController* AICon = Cast<AAIController>(Pedestrian->GetController());
	if (!AICon) return;

	UBlackboardComponent* BB = AICon->GetBlackboardComponent();
	if (!BB) return;

	// Marcar que el peatón ya llegó a la zona de espera
	BB->SetValueAsBool(FName("bAtWaitingPoint"), true);
	BB->SetValueAsObject(FName("CurrentCrosswalk"), this);

	// Determinar el punto de salida al otro lado de la calle
	if (OverlappedComp == WaitingZoneSideA)
	{
		BB->SetValueAsVector(FName("CrosswalkExitPoint"), ExitPointSideB->GetComponentLocation());
	}
	else if (OverlappedComp == WaitingZoneSideB)
	{
		BB->SetValueAsVector(FName("CrosswalkExitPoint"), ExitPointSideA->GetComponentLocation());
	}
}

void ACrosswalk::OnWaitingZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* Pedestrian = Cast<ACharacter>(OtherActor);
	if (!Pedestrian) return;

	AAIController* AICon = Cast<AAIController>(Pedestrian->GetController());
	if (!AICon) return;

	UBlackboardComponent* BB = AICon->GetBlackboardComponent();
	if (BB)
	{
		// Al salir de la caja (empezar a cruzar la calle), desmarcamos el estado de espera
		BB->SetValueAsBool(FName("bAtWaitingPoint"), false);
	}
}