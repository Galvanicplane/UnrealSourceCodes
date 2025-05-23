#include "BaseCharacter.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h" //Random
#include "Components/BoxComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Box Component Oluşturuyoruz
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseCharacter::OnBoxBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseCharacter::OnBoxEndOverlap);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }


}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (IA_Jump)
        {
            EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Started, this, &ABaseCharacter::JumpPressed);
            EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ABaseCharacter::JumpReleased);
        }

        if (IA_Walk)
        {
            EnhancedInput->BindAction(IA_Walk, ETriggerEvent::Triggered, this, &ABaseCharacter::OnWalkTriggered);
        }

        if (IA_Interact)
        {
            EnhancedInput->BindAction(IA_Interact, ETriggerEvent::Started, this, &ABaseCharacter::InInteract);
        }

        if (IA_Attack)
        {
            EnhancedInput->BindAction(IA_Attack, ETriggerEvent::Started, this, &ABaseCharacter::InAttack);
        }

        if (IA_Ability)
        {
            EnhancedInput->BindAction(IA_Ability, ETriggerEvent::Started, this, &ABaseCharacter::InAbility_Implementation);
        }
    }
}


void ABaseCharacter::OnWalkTriggered(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();
    AddMovementInput(FVector::ForwardVector, MovementVector.X);
    AddMovementInput(FVector::RightVector, MovementVector.Y);

}

void ABaseCharacter::JumpPressed()
{
	Jump();
    
}

void ABaseCharacter::JumpReleased()
{
	StopJumping();
}

void ABaseCharacter::InAttack()
{
	if (OverlappingCharacter)
	{
		OverlappingCharacter->MakeAttack();
	}
}

void ABaseCharacter::InInteract()
{
	if (OverlappingCharacter)
	{
		OverlappingCharacter->MakeInteract();
	}
}

void ABaseCharacter::MakeAttack()
{
	if (OverlappingCharacter)
	{
		OverlappingCharacter->TakeAttack(Damage);
	}
}

void ABaseCharacter::MakeInteract()
{
	if (OverlappingCharacter)
	{
		OverlappingCharacter->TakeInteract();
	}
}

void ABaseCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                       bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        if (ABaseCharacter* OtherCharacter = Cast<ABaseCharacter>(OtherActor))
        {
            OverlappingCharacter = OtherCharacter;

            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Got someone!"));
            }
        }
    }
}
void ABaseCharacter::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == OverlappingCharacter)
	{
		OverlappingCharacter = nullptr;
	}
}

void ABaseCharacter::TakeAttack_Implementation(int32 TakenDamage){
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Character took Attack!"));
    }
}

void ABaseCharacter::TakeInteract(){
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Character took Interact!"));
    }
}



void ABaseCharacter::OnRain_Implementation()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("It's Spring!"));
    }
}

void ABaseCharacter::OnHeat_Implementation()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("It's Summer!"));
    }
}

void ABaseCharacter::OnWind_Implementation()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, TEXT("It's Autumn!"));
    }
}


void ABaseCharacter::InAbility_Implementation()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, TEXT("Using ability!"));
    }
}


void ABaseCharacter::MakeEvent_Implementation()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, TEXT("Event going on!"));
    }
}

void ABaseCharacter::Die_Implementation()
{

}

void ABaseCharacter::Tired_Implementation()
{

}