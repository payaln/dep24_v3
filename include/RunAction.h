//
// Created by payaln on 20.02.2019.
//
#pragma once

#include <G4UserRunAction.hh>
#include <G4SystemOfUnits.hh>
#include <G4Run.hh>
#include <array>

#include "DataSaver.h"

#define CHANNEL_COUNT 150
#define SPECTRE_WIDTH (1.5*MeV)

class RunAction : public G4UserRunAction {
public:
    void BeginOfRunAction(const G4Run *aRun) override;
    void EndOfRunAction(const G4Run *aRun) override;
    void AddEvent(size_t channel);
    std::map<G4double, G4double> MakeMapSpectre();

private:
    std::array<size_t, CHANNEL_COUNT> spectr;
};
