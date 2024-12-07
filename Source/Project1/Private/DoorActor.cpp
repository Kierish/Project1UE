



#include "DoorActor.h"
#include "MainCHaracter.h"



ADoorActor::ADoorActor()
{

	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrame->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(DoorFrame);
}

void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &ADoorActor::OpenDoor);
		Timeline.AddInterpFloat(CurveFloat, TimelineProgress);
	}
}

void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);
}

void ADoorActor::OnInteract()
{
	/*UE_LOG(LogTemp, Warning, TEXT("Interacted with door"));
    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Blue, TEXT("Door open/close"));
    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Blue, FString::Printf(TEXT("%d"), bIsDoorClosed));*/
	if (bIsDoorClosed)
	{
		SetDoorOnSameSide();
		Timeline.Play();
	}
	else
	{
		Timeline.Reverse();
	}

	bIsDoorClosed = !bIsDoorClosed;
    //UE_LOG(LogTemp, Warning, TEXT("bIsDoorClosed = %d"), bIsDoorClosed);
}

void ADoorActor::OpenDoor(float Value) 
{
    float Angle = bDoorOnSameSide ? -DoorRotateAngle : DoorRotateAngle;

	FRotator Rot = FRotator(0.f, Angle * Value, 0.f);

	Door->SetRelativeRotation(Rot);
}

void ADoorActor::SetDoorOnSameSide()
{
    if (Character)
    {
        FVector CharacterFV = Character->GetActorForwardVector();
        FVector DoorFV = GetActorForwardVector();

        bDoorOnSameSide = (FVector::DotProduct(CharacterFV, DoorFV) >= 0);
        UE_LOG(LogTemp, Warning, TEXT("%s"), *CharacterFV.ToString());
        UE_LOG(LogTemp, Warning, TEXT("%s"), *DoorFV.ToString());
        UE_LOG(LogTemp, Warning, TEXT("%f"), FVector::DotProduct(CharacterFV, DoorFV));
    }
}