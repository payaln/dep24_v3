//
// Created by payaln on 03.03.2019.
//
#pragma once

#include <G4UImessenger.hh>
#include <G4UIcmdWithABool.hh>
#include <G4UIcmdWithADouble.hh>
#include <G4UIcmdWith3Vector.hh>

#include <functional>
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>

#include "PrimaryPartGenerator.h"

template <typename T>
class GlobalMessenger : public G4UImessenger {
public:
    explicit GlobalMessenger(T* subj);
    ~GlobalMessenger() override;
    void SetNewValue(G4UIcommand *command, G4String newValue) override;
    template <typename Arg>
    GlobalMessenger* AddCommand(G4String cmd, std::function<void(T*, Arg)> func, G4String description = "");

private:
    T* subject;
    G4UIdirectory* directory;

    struct CMD{
        std::shared_ptr<G4UIcommand> cmd;
        std::function<void(T*, G4double)> func;
    };

    struct CMDB{
        std::shared_ptr<G4UIcommand> cmd;
        std::function<void(T*, G4bool)> func;
    };

    std::vector<CMD> commands_d;
    std::vector<CMDB> commands_b;
};


template <typename T>
GlobalMessenger<T>::GlobalMessenger(T* subj) : subject(subj) {
    directory = new G4UIdirectory("/custom_cmd/");
    directory->SetGuidance("custom settings");
}

template <typename T>
GlobalMessenger<T>::~GlobalMessenger() {
    delete directory;
}

template <typename T>
void GlobalMessenger<T>::SetNewValue(G4UIcommand *command, G4String newValue) {
    {
        auto it = std::find_if(commands_d.begin(), commands_d.end(), [&command](const CMD &c) {
            return c.cmd.get() == command;
        });
        if (it != commands_d.end()) {
            it->func(subject, G4UIcmdWithADouble::GetNewDoubleValue(newValue));
        }
    }
    {
        auto it = std::find_if(commands_b.begin(), commands_b.end(), [&command](const CMDB &c) {
            return c.cmd.get() == command;
        });
        if (it != commands_b.end()) {
            it->func(subject, G4UIcmdWithABool::GetNewBoolValue(newValue));
        }
    }
}

template <typename T>
template <typename Arg>
GlobalMessenger<T>* GlobalMessenger<T>::AddCommand(G4String cmd, std::function<void(T*, Arg)> func, G4String description) {
    if (std::is_same<Arg, G4double>::value) {
        commands_d.push_back({std::move(std::shared_ptr<G4UIcommand>(new G4UIcmdWithADouble(G4String(directory->GetCommandPath() + cmd), this))), func});
        commands_d.back().cmd->SetGuidance(description);
    } else if (std::is_same<Arg, G4bool>::value) {
        commands_b.push_back({std::move(std::shared_ptr<G4UIcommand>(new G4UIcmdWithABool(G4String(directory->GetCommandPath() + cmd), this))), func});
        commands_b.back().cmd->SetGuidance(description);
    }
    return this;
}
