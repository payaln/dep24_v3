//
// Created by payaln on 27.02.2019.
//
#include "EventAction.h"

EventAction::EventAction(RunAction* r) : run(r), lostEventEnergy(0.) {}

void EventAction::BeginOfEventAction(const G4Event *anEvent) {
    lostEventEnergy = 0.;
}

void EventAction::EndOfEventAction(const G4Event *anEvent) {
    if (lostEventEnergy > 1e-6) {
        run->AddEvent(static_cast<size_t>(lostEventEnergy / (SPECTRE_WIDTH / CHANNEL_COUNT)));
//        G4cout << lostEventEnergy << G4endl;
    }
}

void EventAction::AddLostEventEnergy(G4double energy) {
    lostEventEnergy += energy;
}