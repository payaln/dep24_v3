//
// Created by payaln on 20.02.2019.
//
#include "Actions.h"

void Actions::Build() const {
    auto run = new RunAction;
    auto event = new EventAction(run);
    auto track = new TrackAction(event);
    SetUserAction(new StepAction(track));
    SetUserAction(track);
    SetUserAction(event);
    SetUserAction(run);
    SetUserAction(new PrimaryPartGenerator);
}

