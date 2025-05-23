// CarMovementComponent.cpp

#include "CarMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"

UCarMovementComponent::UCarMovementComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UCarMovementComponent::InitializeComponent()
{
    Super::InitializeComponent();

    PawnOwner = Cast<APawn>(GetOwner());
    if (!PawnOwner)
    {
        if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, FString::Printf(TEXT("OwnerPawnDüzgün degil") ));
		}
    }
}

void UCarMovementComponent::SetInputVector(const FVector& Input)
{
    InputVector = Input;
}

void UCarMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!PawnOwner || !UpdatedComponent)
        return;


    FVector DesiredMovement = InputVector* Acceleration * DeltaTime;
    
    CarVelocity += DesiredMovement;

    CarVelocity = FMath::VInterpTo(CarVelocity, FVector::ZeroVector, DeltaTime, Friction);
    CarVelocity = CarVelocity.GetClampedToMaxSize(MaxSpeed);

    FVector Delta = CarVelocity * DeltaTime;

    FHitResult Hit;
    SafeMoveUpdatedComponent(Delta, UpdatedComponent->GetComponentRotation(), true, Hit);
	if (GEngine)
    {
        //GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, FString::Printf(TEXT(" InputVector: %s"), *InputVector.ToString()));
    }

    if (Hit.IsValidBlockingHit())
    {
        SlideAlongSurface(Delta, 1.f - Hit.Time, Hit.Normal, Hit);
    }

    // Rotasyon ayarı

    if (bOrientRotationToMovement && !CarVelocity.IsNearlyZero())
    {
        FRotator CurrentRotation = UpdatedComponent->GetComponentRotation();
        FRotator TargetRotation = CarVelocity.Rotation();
        FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationInterpSpeed);
        UpdatedComponent->SetWorldRotation(NewRotation);
    }


    // Reset input vector
    InputVector = FVector::ZeroVector;
}
