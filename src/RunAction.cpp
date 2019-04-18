//
// Created by payaln on 27.02.2019.
//
#include <RunAction.h>

#include "RunAction.h"

void RunAction::BeginOfRunAction(const G4Run *aRun) {
//    spectr.fill(0);
}

void RunAction::EndOfRunAction(const G4Run *aRun) {
    DataSaver::OpenFile("data.txt");
    DataSaver::AddData({spectr.begin(), spectr.end()});
    DataSaver::CloseFile();

    DataSaver::SaveSpectre("spectre.txt", MakeMapSpectre());

    for (const auto& ch : spectr) {
        G4cout << ch << " ";
    }
    G4cout << G4endl;
}

void RunAction::AddEvent(size_t channel) {
    if (channel < CHANNEL_COUNT) {
        ++spectr[channel];
    }
}

std::map<G4double, G4double> RunAction::MakeMapSpectre() {
    std::map<G4double, G4double> res;
    for (size_t ch = 0; ch < CHANNEL_COUNT; ++ch) {
        res[SPECTRE_WIDTH / CHANNEL_COUNT * ch] = spectr[ch];
    }

    return move(res);
}
