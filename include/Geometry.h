//
// Created by payaln on 20.02.2019.
//
#pragma once

#include <cmath>

#include <G4VUserDetectorConstruction.hh>
#include <G4SystemOfUnits.hh>
#include <G4Box.hh>
#include <G4NistManager.hh>
#include <G4LogicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4PVPlacement.hh>
#include <G4VPhysicalVolume.hh>
#include <G4Tubs.hh>
#include <G4UniformElectricField.hh>
#include <G4FieldManager.hh>
#include <G4ClassicalRK4.hh>
#include <G4EqMagElectricField.hh>
#include <G4MagIntegratorDriver.hh>
#include <G4ChordFinder.hh>
#include <G4RunManager.hh>
#include <G4GeometryManager.hh>
#include <G4PhysicalVolumeStore.hh>
#include <G4LogicalVolumeStore.hh>
#include <G4SolidStore.hh>
#include <G4UImanager.hh>
#include "GlobalMessenger.h"

class Geometry : public G4VUserDetectorConstruction {
public:
    Geometry();
    G4VPhysicalVolume *Construct() override;
    void setNewXeDensity(G4double value);

private:
    G4NistManager* nist;
    G4double XeDensity;
};
