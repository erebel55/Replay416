#include "FPSAbilityComponent.h"
#include "ReplayTest416.h"
#include "FPSAbilitySet.h"
#include "FPSCharacter.h"
#include "FPSAbilitySet.h"
#include "FPSAbility.h"
#include "Engine/ActorChannel.h"

// Sets default values for this component's properties
UFPSAbilityComponent::UFPSAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFPSAbilityComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UFPSAbilityComponent, AbilitySet);

}

bool UFPSAbilityComponent::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
    bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
    WroteSomething |= Channel->ReplicateSubobject(AbilitySet, *Bunch, *RepFlags); // replicate the subobject (AbilitySet)
    WroteSomething |= AbilitySet->ReplicateSubobjects(Channel, Bunch, RepFlags); // replicate the subobject's subobjects (Ability)

    return WroteSomething;
}


// Called when the game starts
void UFPSAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

    OwningCharacter = Cast<AFPSCharacter>(GetOwner());
	
    if (GetOwner() && GetOwner()->HasAuthority())
    {
        AbilitySet = NewObject<UFPSAbilitySet>(this, DefaultAbilitySetClass);

        if (AbilitySet)
        {
            for (int32 i = 0; i < AbilitySet->DefaultAbilityClasses.Num(); i++)
            {
                // Create the Ability and set it's Outer
                UFPSAbility* Ability = NewObject<UFPSAbility>(this, AbilitySet->DefaultAbilityClasses[i]);
                Ability->ID = i;

                // Add the Ability to the AbilitySet
                AbilitySet->Abilities.Add(Ability);
            }
        }
    }
}

void UFPSAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFPSAbilityComponent::Start(int32 Index)
{
    if (AbilitySet && AbilitySet->Abilities.IsValidIndex(Index) && AbilitySet->Abilities[Index] != nullptr)
    {
        StartAbility(Index);
    }
}

void UFPSAbilityComponent::StartAbility(int32 Index)
{
    if (OwningCharacter && OwningCharacter->IsLocallyControlled())
    {
        // Start the Ability
        AbilitySet->Abilities[Index]->Start();
    }

    ServerStartAbility(Index);
}

bool UFPSAbilityComponent::ServerStartAbility_Validate(int32 Index)
{
    return true;
}

void UFPSAbilityComponent::ServerStartAbility_Implementation(int32 Index)
{
    // Start the Ability on the Server
    AbilitySet->Abilities[Index]->Start();

    MulticastStartAbility(Index);
}

void UFPSAbilityComponent::MulticastStartAbility_Implementation(int32 Index)
{
    // COMMENT OUT TO FIX
    // Ability doesn't already exist (simulated proxy)
    /*if (AbilitySet && (!AbilitySet->Abilities.IsValidIndex(Index) || AbilitySet->Abilities[Index] == nullptr)) // TODO: cleaner way to write this clause?
    {
        // Create the ability
        UFPSAbility* Ability = NewObject<UFPSAbility>(this, AbilitySet->DefaultAbilityClasses[Index]);
        Ability->ID = Index;

        AbilitySet->Abilities[Index] = Ability;
        Ability->Start();
    }*/
    // END COMMENT OUT TO FIX

    AbilitySet->Abilities[Index]->Start(); // UNCOMMENT TO FIX
}