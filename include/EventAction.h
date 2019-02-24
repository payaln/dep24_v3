//
// Created by payal on 20.02.2019.
//
#pragma once

#include <G4UserEventAction.hh>
#include <G4Event.hh>

class EventAction : public G4UserEventAction {
public:
    void BeginOfEventAction(const G4Event *anEvent) override {
//        G4UserEventAction::BeginOfEventAction(anEvent);
    }

    void EndOfEventAction(const G4Event *anEvent) override {
//        G4UserEventAction::EndOfEventAction(anEvent);
    }
};
