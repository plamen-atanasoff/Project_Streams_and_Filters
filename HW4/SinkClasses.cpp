#define _CRT_SECURE_NO_WARNINGS
#include "SinkClasses.h"
#include <cstring>
#include <fstream>
#include <cassert>
#include "BaseClasses.h"
#include "DynamicArray.hpp"

void ConsoleSink::flush() const {
    sendToStream(std::cout);
}

void FileSink::flush() const {
    std::ofstream ofile(fileName.getC_str());
    if (!ofile.is_open()) {
        std::cerr << "File could not be opened!" << std::endl;
        return;
    }

    sendToStream(ofile);
    ofile.close();
}

void FileSinkMaxK::flush() const {
    source->clear();
    //struct to create the names of the files to save to
    struct {
        MyString name;
        int counter = 1;
        MyString type = ".txt";

        void updateName() {
            counter++;
        }
        MyString getName() {
            return name + to_MyString(counter) + type;
        }
    } currentFileName;
    currentFileName.name = fileName.getSubstring(0, fileName.getSize() - 4);

    MyString fullName = currentFileName.getName();
    std::ofstream ofile(fullName.getC_str(), std::ios::trunc);
    if (!ofile.is_open()) {
        std::cerr << "File could not be opened!" << std::endl;
        return;
    }
    while (sendToStreamMax(ofile, K)) {
        ofile.close();
        currentFileName.updateName();
        fullName = currentFileName.getName();
        ofile.open(fullName.getC_str(), std::ios::trunc);
        if (!ofile.is_open()) {
            std::cerr << "File could not be opened!" << std::endl;
            return;
        }
    }
}

void writeToStreams(const DynamicArray<Sink>& vec) {
    for (int i = 0; i < vec.getSize(); ++i) {
        vec[i].flush();
    }
}

void writeToStreams(DynamicArray<Sink>& vec, DataSource& source) {
    for (int i = 0; i < vec.getSize(); ++i) {
        vec[i].setDataSource(&source);
        vec[i].flush();
    }
}
