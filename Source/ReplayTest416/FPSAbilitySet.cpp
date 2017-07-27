#include "FPSAbilitySet.h"
#include "ReplayTest416.h"
#include "FPSAbility.h"

#include "Engine/ActorChannel.h"

UFPSAbilitySet::UFPSAbilitySet()
{

}

void UFPSAbilitySet::PostInitProperties()
{
    Super::PostInitProperties();

    AActor* OuterActor = Cast<AActor>(GetOuter());
    // COMMENT OUT OT FIX
    /*if (OuterActor && OuterActor->Role == ROLE_SimulatedProxy)
    {
        // Size the array to match the same number of abilities
        // These will be null until they are activated
        // So if an element is non-null it is active
        // and if an element is null it is not active
        Abilities.SetNum(DefaultAbilityClasses.Num());
    }*/
    // END COMMENT OUT TO FIX
}

bool UFPSAbilitySet::IsSupportedForNetworking() const
{
    return true;
}

void UFPSAbilitySet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Replicate Abilities to owning client only
    //DOREPLIFETIME_CONDITION(UFPSAbilitySet, Abilities, /*COND_OwnerOnly*/ COND_ReplayOrOwner); // COMMENT OUT TO FIX
    DOREPLIFETIME(UFPSAbilitySet, Abilities); // UNCOMMENT TO FIX
}

bool UFPSAbilitySet::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
    //bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
    bool WroteSomething = false;

    for (UFPSAbility* Ability : Abilities)
    {
        if (Ability)
        {
            WroteSomething |= Channel->ReplicateSubobject(Ability, *Bunch, *RepFlags);
        }
    }

    return WroteSomething;
}

