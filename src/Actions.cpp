//
// Created by payaln on 20.02.2019.
//
#include "Actions.h"

void Actions::Build() const {
    SetUserAction(new StepAction);
    SetUserAction(new RunAction);
    SetUserAction(new PrimaryPartGenerator);
    SetUserAction(new EventAction);
}

