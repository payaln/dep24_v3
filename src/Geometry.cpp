//
// Created by payaln on 20.02.2019.
//

#include "Geometry.h"

G4VPhysicalVolume *Geometry::Construct() {

    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    auto size = 15 * cm;

    nist = G4NistManager::Instance();
    auto world_mat = nist->FindOrBuildMaterial("G4_Galactic");
    auto world = new G4Box("world", size, size, size);
    auto world_log = new G4LogicalVolume(world, world_mat, "world_log");
    world_log->SetVisAttributes(G4Color(1, 1, 1, .0));
    auto world_PV = new G4PVPlacement(nullptr, {}, world_log, "world_PV", nullptr, false, 0);

    auto source_mat = nist->FindOrBuildMaterial("G4_Galactic");
    auto source = new G4Box("source", 0.5 * mm, 6 * cm, 10 * cm);
    auto source_log = new G4LogicalVolume(source, source_mat, "source_log");
    source_log->SetVisAttributes(G4Color::Green());
    new G4PVPlacement(nullptr, {7 * cm, 0, 0}, source_log, "source_PV", world_log, false, 0);

    auto detector_mat = new G4Material("Xenon", 54., 131. * g/mole, XeDensity * g/cm3);
    auto detector = new G4Tubs("detector" , 2 * mm, 60 * mm, 10 * cm, 0 * deg, 360 * deg);
    auto detector_log = new G4LogicalVolume(detector, detector_mat, "detector_log");
    detector_log->SetVisAttributes(G4Color::Blue());

    new G4PVPlacement(nullptr, {-5 * cm, 0, 0}, detector_log, "detector_PV", world_log, false, 0);

    auto anode_mat = nist->FindOrBuildMaterial("G4_Cu");
    auto anode = new G4Tubs("anode", 0 * mm, 2 * mm, 10 * cm, 0 * deg, 360 * deg);
    auto anode_log = new G4LogicalVolume(anode, anode_mat, "anode_log");
    anode_log->SetVisAttributes(G4Color::Brown());
    new G4PVPlacement(nullptr, {-5 * cm, 0, 0}, anode_log, "anode_PV", world_log, false, 0);

    return world_PV;
}

Geometry::Geometry() : XeDensity(0.3), E_in_KV(50.) {
    (new GlobalMessenger<Geometry>(this))
            ->AddCommand<G4double>("set_Xe_density", &Geometry::setNewXeDensity, "density Xe")
            ->AddCommand<G4double>("set_E_KV", &Geometry::setNewE, "set electric field strength");
    new MyVisCommandSceneAddElectricField();
}

void Geometry::setNewXeDensity(G4double value) {
    XeDensity = value;
    resetGeometry();
}

void Geometry::setNewE(G4double value) {
    E_in_KV = value;
    if (!fField) {
        fField->setEr(E_in_KV);
    }
    resetGeometry();
}

void Geometry::resetGeometry() {
    G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
    G4RunManager::GetRunManager()->ReinitializeGeometry();
}

G4ThreadLocal ElectricField* Geometry::fField = 0;

void Geometry::ConstructSDandField() {
    if (!fField) {
        fField = new ElectricField(E_in_KV, {-50. * mm, 0., 0.});

        G4EqEMFieldWithSpin* equation = new G4EqEMFieldWithSpin(fField);

        G4FieldManager* fieldManager
                = G4TransportationManager::GetTransportationManager()->GetFieldManager();
        fieldManager->SetDetectorField(fField);

        G4MagIntegratorStepper* stepper = new G4ClassicalRK4(equation,12);

        auto fIntgrDriver = new G4MagInt_Driver(0.01*mm,
                                                stepper,
                                                stepper->GetNumberOfVariables());
        auto chordFinder = new G4ChordFinder(fIntgrDriver);

        fieldManager->SetChordFinder(chordFinder);
    }
}
