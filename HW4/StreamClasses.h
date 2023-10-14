#pragma once
#include <iostream>
#include "BaseClasses.h"
#include "DynamicArray.hpp"

class ConsoleStream : public Stream {
private:
	virtual Stream* clone() const override {
		return new ConsoleStream(*this);
	}
public:
	ConsoleStream();
};

class ConstStream : public Stream {
private:
	virtual Stream* clone() const override {
		return new ConstStream(*this);
	}
public:
	ConstStream(const MyString& str);
};

class FileStream : public Stream {
private:
	virtual Stream* clone() const override {
		return new FileStream(*this);
	}
public:
	FileStream(const char* fileName);
};

//Трябва да може да се чете съдържание от множество входни източника.
//Съдържанието от всичките източници трябва да се долепи едно след друго.
MyString readFromStreams(const DynamicArray<Stream>& vec);
