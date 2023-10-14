#define _CRT_SECURE_NO_WARNINGS
#include "SinkClasses.h"
#include <cstring>
#include <fstream>
#include <cassert>
#include "BaseClasses.h"
#include "DynamicArray.hpp"

ConsoleSink::ConsoleSink(DataSource& obj) : Sink(&obj) {}

void ConsoleSink::flush() const {
    sendToStream(std::cout);
}

FileSink::FileSink(const MyString& fileName) : fileName(fileName) {}

FileSink::FileSink(DataSource& obj, const MyString& fileName) : Sink(&obj), fileName(fileName) {}

void FileSink::flush() const {
    std::ofstream ofile(fileName.getC_str());
    if (!ofile.is_open()) {
        std::cerr << "File could not be opened!" << std::endl;
        return;
    }

    sendToStream(ofile);
    ofile.close();
}

FileSinkMaxK::FileSinkMaxK(const MyString& fileName, int maxChars) : fileName(fileName), K(maxChars) {}

FileSinkMaxK::FileSinkMaxK(DataSource& obj, const MyString& fileName, int maxChars)
    : Sink(&obj), fileName(fileName), K(maxChars) {
    if (maxChars <= 0) {
        throw std::invalid_argument("maxChars must be positive!");
    }
}

void FileSinkMaxK::flush() const {
    source->clear();
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

void writeToStreams(const DynamicVector<Sink>& vec) {
    for (int i = 0; i < vec.getSize(); ++i) {
        vec[i].flush();
    }
}

void writeToStreams(DynamicVector<Sink>& vec, DataSource& source) {
    for (int i = 0; i < vec.getSize(); ++i) {
        vec[i].setDataSource(&source);
        vec[i].flush();
    }
}
