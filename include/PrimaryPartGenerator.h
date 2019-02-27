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

class PrimaryPartGenerator : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryPartGenerator();
    void GeneratePrimaries(G4Event *anEvent) override;

private:
    G4ParticleGun* GGamma;

    void GenEnergy();
};
