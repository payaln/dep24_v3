//
// Created by payaln on 27.02.2019.
//
#pragma once

#include <G4UserTrackingAction.hh>
#include <G4ParticleDefinition.hh>
#include <G4Track.hh>

#include "EventAction.h"

class TrackAction : public G4UserTrackingAction {
public:
    explicit TrackAction(EventAction* e);
    void PreUserTrackingAction(const G4Track *track) override;
    void PostUserTrackingAction(const G4Track* track) override;
    void AddLostEnergy(G4double energy);

private:
    EventAction* event;
    G4double lostEnergy;
};
