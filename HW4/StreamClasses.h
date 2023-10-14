#pragma once
#include <iostream>
#include "BaseClasses.h"
#include "DynamicArray.hpp"

class ConsoleStream : public Stream {
private:
	virtual Stream* clone() const override {
		return DBG_NEW ConsoleStream(*this);
	}
public:
	ConsoleStream();
};

class ConstStream : public Stream {
private:
	virtual Stream* clone() const override {
		return DBG_NEW ConstStream(*this);
	}
public:
	ConstStream(const MyString& str);
};

class FileStream : public Stream {
private:
	virtual Stream* clone() const override {
		return DBG_NEW FileStream(*this);
	}
public:
	FileStream(const char* fileName);
};

MyString readFromStreams(const DynamicVector<Stream>& vec);
