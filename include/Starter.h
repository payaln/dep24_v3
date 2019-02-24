//
// Created by payaln on 20.02.2019.
//

#pragma once

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QBBC.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include <memory>

#include "Geometry.h"
#include "Actions.h"

class Starter {
public:
    Starter(int argc, char** argv);
private:
    std::shared_ptr<G4RunManager> runManager;
#ifdef G4VIS_USE
    std::shared_ptr<G4VisManager> visManager;
#endif
};