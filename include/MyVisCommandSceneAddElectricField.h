//
// Created by aleksey on 18.04.2019.
//

#pragma once

#include "G4VVisCommand.hh"
#include "G4VisCommandsScene.hh"
#include "G4VisAttributes.hh"

class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;

#include "MyElectricFieldModel.h"

class MyVisCommandSceneAddElectricField : public G4VVisCommandScene {
public:
    MyVisCommandSceneAddElectricField();
    virtual ~MyVisCommandSceneAddElectricField();
    G4String GetCurrentValue (G4UIcommand* command) override;
    void SetNewValue (G4UIcommand* command, G4String newValue) override;

private:
    MyVisCommandSceneAddElectricField (const MyVisCommandSceneAddElectricField&);
    MyVisCommandSceneAddElectricField& operator = (const MyVisCommandSceneAddElectricField&);
    G4UIcommand* fpCommand;
};
