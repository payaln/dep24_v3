//
// Created by payaln on 27.02.2019.
//
#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class DataSaver {
public:

    static std::ofstream out;
    static std::string splitter;

    static void CreateFile(const std::string& filename);
    static void OpenFile(const std::string& filename);
    static void CloseFile();
    static void SetSplitter(const std::string& s);
    static std::string GetSplitter();
    static void AddData(const std::vector<double>& data);
    static void SaveSpectre(const std::string& filename, const std::map<double, double>& data);
};
