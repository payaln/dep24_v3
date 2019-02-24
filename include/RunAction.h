//
// Created by payal on 20.02.2019.
//
#pragma once

#include <G4UserRunAction.hh>
#include <G4Run.hh>

class RunAction : public G4UserRunAction {
public:
    void BeginOfRunAction(const G4Run *aRun) override {
//        G4UserRunAction::BeginOfRunAction(aRun);
    }

    void EndOfRunAction(const G4Run *aRun) override {
//        G4UserRunAction::EndOfRunAction(aRun);
    }
};
