//
// Created by payaln on 20.02.2019.
//
#pragma once

#include <G4UserEventAction.hh>
#include <G4Event.hh>

#include "RunAction.h"


class EventAction : public G4UserEventAction {
public:
    explicit EventAction(RunAction* r);
    void BeginOfEventAction(const G4Event *anEvent) override;
    void EndOfEventAction(const G4Event *anEvent) override;
    void AddLostEventEnergy(G4double energy);

private:
    RunAction* run;
    G4double lostEventEnergy;
};
