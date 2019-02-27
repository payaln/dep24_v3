//
// Created by payaln on 20.02.2019.
//
#pragma once

#include <G4UserSteppingAction.hh>
#include <G4Step.hh>

#include "TrackAction.h"

class StepAction : public G4UserSteppingAction  {
public:
    explicit StepAction(TrackAction* tr);
    void UserSteppingAction(const G4Step *step) override;

private:
    TrackAction* track;
};
