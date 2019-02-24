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
#include <G4TransportationManager.hh>


class Geometry : public G4VUserDetectorConstruction {
public:
    G4VPhysicalVolume *Construct() override;

private:
    G4NistManager* nist;
};
