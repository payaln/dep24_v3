//
// Created by payaln on 27.02.2019.
//
#include "DataSaver.h"


std::ofstream DataSaver::out;
std::string DataSaver::splitter = " ";

void DataSaver::CreateFile(const std::string& filename) {
    out.open(filename);
}

void DataSaver::OpenFile(const std::string& filename) {
    out.open(filename, std::ios::app);
}

void DataSaver::CloseFile() {
    out << std::endl;
    out.close();
}

void DataSaver::SetSplitter(const std::string& s) {
    splitter = s;
}

std::string DataSaver::GetSplitter() {
    return splitter;
}

void DataSaver::AddData(const std::vector<double>& data) {
    for (const auto& d : data) {
        out << d << splitter;
    }
    out << std::endl;
}

void DataSaver::SaveSpectre(const std::string &filename, const std::map<double, double> &data) {
    std::ofstream out_s(filename);
//    for (const auto& [ch, cnt] : data) {
//        out << ch << splitter << cnt << std::endl;
//    }
    for (const auto& d : data) {
        out_s << d.first << splitter << d.second << std::endl;
    }
    out_s.close();
}
