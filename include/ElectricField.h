//
// Created by payal on 05.03.2019.
//
#pragma once

#include <G4ElectroMagneticField.hh>
#include <G4SystemOfUnits.hh>
#include <G4ThreeVector.hh>

class ElectricField : public G4ElectroMagneticField {
public:
    ElectricField(G4double E, const G4ThreeVector& pos);
    virtual ~ElectricField();

    G4bool DoesFieldChangeEnergy() const override;
    void GetFieldValue(const G4double *Point, G4double *Bfield) const override;

    void setEr(G4double Er);

private:
    G4double Er;
    G4ThreeVector detector_pos;
};
