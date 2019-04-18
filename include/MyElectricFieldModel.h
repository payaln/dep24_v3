//
// Created by aleksey on 18.04.2019.
//

#pragma once

#include <G4VModel.hh>
#include <G4VGraphicsScene.hh>
#include <G4TransportationManager.hh>
#include <G4Field.hh>
#include <G4FieldManager.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>
#include <G4Polyline.hh>
#include <G4ArrowModel.hh>

class MyElectricFieldModel : public G4VModel {
public:
    enum Representation {fullArrow, lightArrow};

    MyElectricFieldModel(G4int fNDataPointsPerMaxHalfScene = 5,
                         const Representation &fRepresentation = Representation::fullArrow,
                         G4int fArrow3DLineSegmentsPerCircle = 6);

    virtual ~MyElectricFieldModel();

    void DescribeYourselfTo(G4VGraphicsScene &scene) override;

private:
    MyElectricFieldModel (const MyElectricFieldModel&);
    MyElectricFieldModel& operator = (const MyElectricFieldModel&);

    G4int fNDataPointsPerMaxHalfScene;
    Representation fRepresentation;
    G4int fArrow3DLineSegmentsPerCircle;
};