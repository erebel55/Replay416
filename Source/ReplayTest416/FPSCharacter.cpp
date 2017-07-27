#include "FPSCharacter.h"
#include "ReplayTest416.h"
#include "FPSAbilityComponent.h"


// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create the ability component
    AbilityComponent = CreateDefaultSubobject<UFPSAbilityComponent>(TEXT("AbilityComponent"));
    // Replicate the ability component
    AbilityComponent->SetIsReplicated(true);

    // Create the third person camera arm
    ThirdPersonCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonCameraArm"));
    ThirdPersonCameraArm->SetupAttachment(GetCapsuleComponent());
    ThirdPersonCameraArm->bUsePawnControlRotation = true;
    // Default position
    ThirdPersonCameraArm->SocketOffset = FVector(0, 35, 55);
    ThirdPersonCameraArm->TargetOffset = FVector(0, 0, 0);

    // Create the third person camera
    ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
    ThirdPersonCameraComponent->SetupAttachment(ThirdPersonCameraArm);

}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::StartAbility);
    //PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::PlayAnimation);
}

void AFPSCharacter::StartAbility()
{
    if (AbilityComponent)
    {
        AbilityComponent->Start(0);
    }
}