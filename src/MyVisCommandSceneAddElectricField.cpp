//
// Created by aleksey on 18.04.2019.
//

#include "MyVisCommandSceneAddElectricField.h"

#include "G4UIcmdWithAnInteger.hh"
#include "G4VisManager.hh"
#include "G4TransportationManager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4PhysicalVolumeModel.hh"
#include "G4ApplicationState.hh"
#include "G4UImanager.hh"
#include "G4UIcommand.hh"

G4VisManager * MyVisCommandSceneAddElectricField::G4VVisCommand::fpVisManager;

MyVisCommandSceneAddElectricField::MyVisCommandSceneAddElectricField() {
    fpCommand = new G4UIcommand ("/vis/scene/add/electricField", this);
    G4UIparameter* parameter;
    parameter = new G4UIparameter ("nDataPointsPerHalfScene", 'i', true);
    parameter -> SetDefaultValue (5);
    fpCommand -> SetParameter (parameter);
}


MyVisCommandSceneAddElectricField::~MyVisCommandSceneAddElectricField() {
    delete fpCommand;
}

G4String MyVisCommandSceneAddElectricField::GetCurrentValue(G4UIcommand *command) {
    return "";
}

void MyVisCommandSceneAddElectricField::SetNewValue(G4UIcommand *command, G4String newValue) {
    fpVisManager = G4VisManager::GetInstance();
    G4VisManager::Verbosity verbosity = fpVisManager->GetVerbosity();
    G4bool warn(verbosity >= G4VisManager::warnings);
    G4Scene* pScene = fpVisManager->GetCurrentScene();

    if (!pScene) {
        if (verbosity >= G4VisManager::errors) {
            G4cout << "ERROR: No current scene.  Please create one." << G4endl;
        }
        return;
    }
    G4int nDataPointsPerHalfScene;
    std::istringstream iss(newValue);
    iss >> nDataPointsPerHalfScene;

    G4VModel* model = new MyElectricFieldModel(nDataPointsPerHalfScene, MyElectricFieldModel::fullArrow, 3);
    const G4String& currentSceneName = pScene -> GetName ();
    G4bool successful = pScene -> AddRunDurationModel (model, warn);
    if (successful) {
        if (verbosity >= G4VisManager::confirmations) {
            G4cout << "Electric field, if any, will be drawn in scene \""
            << currentSceneName
            << "\"\n  with "
            << nDataPointsPerHalfScene << " data points per half scene."
            << G4endl;
        }
    } else {
        if (verbosity >= G4VisManager::warnings) {
            G4cout << "WARNING: For some reason, possibly mentioned above, it has not been\n  possible to add to the scene." << G4endl;
        }
    }
    CheckSceneAndNotifyHandlers (pScene);
}

