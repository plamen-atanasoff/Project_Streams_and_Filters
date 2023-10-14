#define _CRT_SECURE_NO_WARNINGS
#include "SinkClasses.h"
#include <cstring>
#include <fstream>
#include <cassert>
#include "BaseClasses.h"
#include "DynamicArray.hpp"

ConsoleSink::ConsoleSink(DataSource& obj) : Sink(obj) {}

void ConsoleSink::flush() const {
    sendToStream(std::cout);
}

FileSink::FileSink(DataSource& obj, const MyString& fileName) : Sink(obj), fileName(fileName) {}

void FileSink::flush() const {
    std::ofstream ofile(fileName.getC_str());
    if (!ofile.is_open()) {
        std::cerr << "File could not be opened!" << std::endl;
        return;
    }

    sendToStream(ofile);
    ofile.close();
}

void FileSink::flushMax(int size) const {
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

    std::ofstream ofile;
    while (true) {
        MyString fullName = currentFileName.getName();
        ofile.open(fullName.getC_str(), std::ios::trunc);
        if (!ofile.is_open()) {
            std::cerr << "File could not be opened!" << std::endl;
            return;
        }
        if (!sendToStreamMax(ofile, size)) {
            break;
        }
        ofile.close();
        currentFileName.updateName();
    }
}

OutputStreamVector::OutputStreamVector(DataSource& source) : source(source) {}

void OutputStreamVector::setSource(DataSource& newSource) {
    source = newSource;
    for (int i = 0; i < DynamicVector<Sink>::getSize(); ++i) {
        DynamicVector<Sink>::operator[](i).setDataSource(source);
    }
}

void writeToStreams(const OutputStreamVector& vec) {
    for (int i = 0; i < vec.getSize(); ++i) {
        vec[i].flush();
    }
}
