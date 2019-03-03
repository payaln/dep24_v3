//
// Created by payaln on 20.02.2019.
//
#pragma once

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <G4Event.hh>
#include <G4Gamma.hh>
#include <G4ParticleTable.hh>
#include <G4SystemOfUnits.hh>
#include <Randomize.hh>

#include "GlobalMessenger.h"

class PrimaryPartGenerator : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryPartGenerator();
    void GeneratePrimaries(G4Event *anEvent) override;
    void setSingleEnergy(G4bool singleEnergy);

private:
    G4ParticleGun* GGamma;
    G4bool singleEnergy;

    void GenEnergy();
};
