#include "FPSAbility.h"
#include "ReplayTest416.h"
#include "FPSCharacter.h"
#include "FPSAbilityComponent.h"
#include "FPSAbilitySet.h"

UFPSAbility::UFPSAbility()
{
    ID = 0;
}

void UFPSAbility::PostInitProperties()
{
    Super::PostInitProperties();

    AbilityComponent = Cast<UFPSAbilityComponent>(GetOuter());
    if (AbilityComponent)
    {
        Character = Cast<AFPSCharacter>(AbilityComponent->GetOwner());
    }
    // TESTING - On Client GetOuter() returns Character instead of AbilityComponent
    else
    {
        Character = Cast<AFPSCharacter>(GetOuter());
        if (Character)
        {
            AbilityComponent = Character->AbilityComponent;
        }
    }
}

bool UFPSAbility::IsSupportedForNetworking() const
{
    return true;
}

void UFPSAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    //DOREPLIFETIME_CONDITION(UFPSAbility, Animation, /*COND_OwnerOnly*/ COND_ReplayOrOwner); // COMMENT OUT TO FIX
    //DOREPLIFETIME_CONDITION(UFPSAbility, ID, /*COND_OwnerOnly*/ COND_ReplayOrOwner);// COMMENT OUT TO FIX

    DOREPLIFETIME(UFPSAbility, Animation);     // UNCOMMENT TO FIX
    DOREPLIFETIME(UFPSAbility, ID);     // UNCOMMENT TO FIX
}

void UFPSAbility::Start()
{
    if (Character && Animation.Pawn3P)
    {
        // Play the Third Person Animation
        Character->PlayAnimMontage(Animation.Pawn3P);
    }

    Execute();
}

void UFPSAbility::Execute()
{
    End();
}

void UFPSAbility::End()
{
    // COMMENT OUT TO FIX
    /*if (Character && Character->Role == ROLE_SimulatedProxy)
    {
        if (AbilityComponent && AbilityComponent->AbilitySet && AbilityComponent->AbilitySet->Abilities.IsValidIndex(ID))
        {
            // Remove the ability
            AbilityComponent->AbilitySet->Abilities[ID] = nullptr;
        }
    }*/
    // END COMMENT OUT TO FIX
}
