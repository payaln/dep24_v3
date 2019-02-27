//
// Created by payaln on 27.02.2019.
//
#include "TrackAction.h"

TrackAction::TrackAction(EventAction* e) : event(e), lostEnergy(0.) {}

void TrackAction::PreUserTrackingAction(const G4Track *track) {
    lostEnergy = 0.;
}

void TrackAction::PostUserTrackingAction(const G4Track* track) {
    if (track->GetParticleDefinition()->GetParticleName() =="e-") {
        event->AddLostEventEnergy(lostEnergy);
    }
}

void TrackAction::AddLostEnergy(G4double energy) {
    lostEnergy += energy;
}
