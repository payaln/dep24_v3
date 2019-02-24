//
// Created by payaln on 20.02.2019.
//
#include <Starter.h>

Starter::Starter(int argc, char **argv) {
    runManager = std::make_shared<G4RunManager>();
    runManager->SetUserInitialization(new Geometry);
    runManager->SetUserInitialization(new QBBC);
    runManager->SetUserInitialization(new Actions);
    runManager->Initialize();
#ifdef G4VIS_USE
    visManager = std::make_shared<G4VisExecutive>();
    visManager->Initialize();
#endif
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if (argc != 1) {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    } else {

#ifdef G4UI_USE
        G4UIExecutive *ui = new G4UIExecutive(argc, argv, "qt");
#ifdef G4VIS_USE
        UImanager->ApplyCommand("/control/execute init_vis.mac");
#else
        UImanager->ApplyCommand("/control/execute init.mac");
#endif
        ui->SessionStart();
        delete ui;
#endif
    }
}

