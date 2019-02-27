//
// Created by payaln on 20.02.2019.
//
#pragma once

#include <G4VUserActionInitialization.hh>

#include "PrimaryPartGenerator.h"
#include "EventAction.h"
#include "RunAction.h"
#include "StepAction.h"
#include "TrackAction.h"

class Actions : public G4VUserActionInitialization {
public:
    void Build() const override;
};
