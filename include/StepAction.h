//
// Created by payaln on 20.02.2019.
//
#pragma once

#include <G4UserSteppingAction.hh>
#include <G4Step.hh>

class StepAction : public G4UserSteppingAction  {
public:
    void UserSteppingAction(const G4Step *step) override {
//        G4UserSteppingAction::UserSteppingAction(step);
    }
};
