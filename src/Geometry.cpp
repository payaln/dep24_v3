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
    new G4PVPlacement(nullptr, {10 * cm, 0, 0}, source_log, "source_PV", world_log, false, 0);

//    auto cathode_mat = nist->FindOrBuildMaterial("G4_Cu");
//    auto cathode = new G4Tubs("cathode", 19 * mm, 19.1 * mm, 10 * cm, 0, 360 * degree);
//    auto cathode_log = new G4LogicalVolume(cathode, cathode_mat, "cathode_log");
//    cathode_log->SetVisAttributes(G4Color::Brown());
//    new G4PVPlacement(nullptr, {-5 * cm, 0, 0}, cathode_log, "cathode_PV", world_log, false, 0);

//    auto detector_mat = nist->FindOrBuildMaterial("G4_lXe");
    auto detector_mat = new G4Material("Xenon", 54., 131. * g/mole, XeDensity * g/cm3);
    G4int sector_size = 18;
    for (size_t i = 0; i < 360 / sector_size; ++i) {
        auto detector = new G4Tubs("detector" + std::to_string(i), 2 * mm, 19 * mm, 10 * cm, i * sector_size * degree, sector_size * degree);
        auto detector_log = new G4LogicalVolume(detector, detector_mat, "detector_log" + std::to_string(i));
        detector_log->SetVisAttributes(G4Color::Blue());

        G4double E = 50. * kilovolt / cm;
        auto fEMfield = new G4UniformElectricField(
                G4ThreeVector(E * std::cos(sector_size * degree * (i + 0.5)), E * std::sin(sector_size * degree * (i + 0.5)), 0.0));
        auto fmanager = new G4FieldManager(fEMfield);
        auto fEquation = new G4EqMagElectricField(fEMfield);
        auto fStepper = new G4ClassicalRK4( fEquation, 8 );
        auto fIntgrDriver = new G4MagInt_Driver(0.2*mm,
                                                fStepper,
                                                fStepper->GetNumberOfVariables());
        auto fChordFinder = new G4ChordFinder(fIntgrDriver);
        fmanager->SetChordFinder( fChordFinder );
        detector_log->SetFieldManager(fmanager, false);

        new G4PVPlacement(nullptr, {-5 * cm, 0, 0}, detector_log, "detector_PV" + std::to_string(i), world_log, false, 0);
    }


    auto anode_mat = nist->FindOrBuildMaterial("G4_Cu");
    auto anode = new G4Tubs("anode", 0 * mm, 2 * mm, 10 * cm, 0 * deg, 360 * deg);
    auto anode_log = new G4LogicalVolume(anode, anode_mat, "anode_log");
    anode_log->SetVisAttributes(G4Color::Brown());
    new G4PVPlacement(nullptr, {-5 * cm, 0, 0}, anode_log, "anode_PV", world_log, false, 0);

    return world_PV;
}

Geometry::Geometry() : XeDensity(3.5) {
    (new GlobalMessenger<Geometry>(this))->AddCommand<G4double>("set_Xe_density", &Geometry::setNewXeDensity, "density Xe");
}

void Geometry::setNewXeDensity(G4double value) {
    XeDensity = value;
    G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
    G4RunManager::GetRunManager()->ReinitializeGeometry();
}
