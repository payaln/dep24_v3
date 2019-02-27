//
// Created by payaln on 27.02.2019.
//
#include "StepAction.h"

StepAction::StepAction(TrackAction* tr) : track(tr) {}

void StepAction::UserSteppingAction(const G4Step *step) {
    if (step->GetPostStepPoint()->GetPhysicalVolume() != nullptr) {
        if (step->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "anode_PV") {
            track->AddLostEnergy(
                    step->GetPreStepPoint()->GetKineticEnergy() -
                    step->GetPostStepPoint()->GetKineticEnergy()
            );
        }
    }
}
