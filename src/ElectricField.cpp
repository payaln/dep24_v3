//
// Created by payal on 05.03.2019.
//
#include "ElectricField.h"


ElectricField::ElectricField(G4double E, const G4ThreeVector& pos)
    : G4ElectroMagneticField(), Er(E * kilovolt/cm), detector_pos(pos) {

}

ElectricField::~ElectricField() {

}

G4bool ElectricField::DoesFieldChangeEnergy() const {
    return true;
}

void ElectricField::GetFieldValue(const G4double *Point, G4double *Bfield) const {
    const G4ThreeVector pos = {
            Point[0] - detector_pos.getX(),
            Point[1] - detector_pos.getY(),
            Point[3] - detector_pos.getZ()
    };

    G4double posR = std::sqrt(std::pow(pos.getX(), 2) + std::pow(pos.getY(), 2));
    G4double cos_theta, sin_theta;
    G4double Ex, Ey;

    if ( posR < 60 * mm && posR > 2 * mm) {
        cos_theta = pos[0] / posR;
        sin_theta = pos[1] / posR;
        Ex = Er * cos_theta;
        Ey = Er * sin_theta;
    } else {
        Ex = 0;
        Ey = 0;
    }

    Bfield[0]=0;
    Bfield[1]=0;
    Bfield[2]=0;

    Bfield[3]=Ex;
    Bfield[4]=Ey;
    Bfield[5]=0;
}

void ElectricField::setEr(G4double Er) {
    ElectricField::Er = Er * kilovolt/cm;
}
