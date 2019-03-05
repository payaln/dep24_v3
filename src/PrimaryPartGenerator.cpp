//
// Created by payaln on 20.02.2019.
//
#include "PrimaryPartGenerator.h"


void PrimaryPartGenerator::GeneratePrimaries(G4Event *anEvent) {
    GGamma->SetParticleMomentumDirection({-1.,G4RandFlat::shoot(-0.5, 0.5),G4RandFlat::shoot(-0.5, 0.5)});
    GenEnergy();
    GGamma->SetParticlePosition({70 * mm, G4RandFlat::shoot(-50, 50) * mm, G4RandFlat::shoot(-100, 100) * mm});
    GGamma->GeneratePrimaryVertex(anEvent);
}

PrimaryPartGenerator::PrimaryPartGenerator() {

    (new GlobalMessenger<PrimaryPartGenerator>(this))
        ->AddCommand<G4bool>("set_single_energy", &PrimaryPartGenerator::setSingleEnergy, "set single(true) or mix(false) energy");

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle
            = particleTable->FindParticle("gamma");
    GGamma = new G4ParticleGun(1);
    GGamma->SetParticleDefinition(particle);
}

void PrimaryPartGenerator::GenEnergy() {
    G4int k_E;
    if (singleEnergy) {
        k_E = 1;
    } else {
        k_E = G4RandFlat::shootInt(5);
    }
    switch (k_E) {
        case 0:
            GGamma->SetParticleEnergy(662*keV);
            break;
        case 1:
            GGamma->SetParticleEnergy(1173*keV);
            break;
        case 2:
            GGamma->SetParticleEnergy(1332*keV);
            break;
        case 3:
            GGamma->SetParticleEnergy(122*keV);
            break;
        case 4:
            GGamma->SetParticleEnergy(511*keV);
            break;
        default:
            break;
    }
}

void PrimaryPartGenerator::setSingleEnergy(G4bool singleEnergy) {
    PrimaryPartGenerator::singleEnergy = singleEnergy;
}
