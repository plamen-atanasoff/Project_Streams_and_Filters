#define _CRT_SECURE_NO_WARNINGS
#include "StreamClasses.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include <fstream>
#include <exception>
#include "MyString.h"
#include "DynamicArray.hpp"

ConsoleStream::ConsoleStream() {
    readFromStream(std::cin);
}

ConstStream::ConstStream(const MyString& str) {
    data = str;
}

FileStream::FileStream(const char* fileName) {
	if (!fileName) {
		throw std::invalid_argument("File name is nullptr!");
	}

	std::ifstream ifile(fileName);
	if (!ifile.is_open()) {
		throw std::runtime_error("File could not be opened!");
	}

	readFromStream(ifile);
}

MyString readFromStreams(const DynamicVector<Stream>& vec) {
    MyString res;
    for (int i = 0; i < vec.getSize(); ++i) {
        char ch;
        vec[i].clear();
        while (vec[i].getSymbol(ch)) {
            res.pushBack(ch);
        }
    }
    return res;
}
