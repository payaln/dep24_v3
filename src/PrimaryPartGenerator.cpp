//
// Created by payaln on 20.02.2019.
//
#include "PrimaryPartGenerator.h"

void PrimaryPartGenerator::GeneratePrimaries(G4Event *anEvent) {
    GGamma->GeneratePrimaryVertex(anEvent);
}

PrimaryPartGenerator::PrimaryPartGenerator() {

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    G4ParticleDefinition* particle
            = particleTable->FindParticle(particleName="gamma");
    GGamma = new G4ParticleGun(1);
//    GGamma->SetParticleDefinition(G4Gamma::GammaDefinition());
    GGamma->SetParticleDefinition(particle);

    GGamma->SetParticlePosition({100, 0, 0});
    CLHEP::RandFlat(CLHEP)
    GGamma->SetParticleMomentumDirection({-1.,CLHEP::RandFlat::shoot(-1, 1),CLHEP::RandFlat::shoot(-1, 1)});
    GGamma->SetParticleEnergy(2*MeV);
}
