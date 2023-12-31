﻿#pragma once
#include <iostream>
#include <cassert>
#include "MyString.h"

class DataSource {
protected:
	MyString data;
	mutable int pointer = 0; //pointer to the current symbol of data

	void validateState() const;
public:
	virtual ~DataSource() = default;

	bool getSymbol(char& symbol) const;
	void clear() const;
	bool isValid() const;
};

//Потребителят може да имплементира свои обекти, които изходи или източници на съдържание.
//За да работят с останалата част от кода трябва да наследят съответно Stream или Sink 
//и да предефинират съответните им чисто виртуални методи.
class Stream : public DataSource {
protected:
	void readFromStream(std::istream& is);
public:
	virtual Stream* clone() const = 0;
};

class Filter : public DataSource {
protected:
	void initContent(const DataSource& obj);
public:
	virtual ~Filter() = default;

	virtual MyString filter(const MyString& toFilter) const = 0;
	virtual Filter* clone() const = 0;
};

class Sink {
protected:
	DataSource* source = nullptr;

	Sink() = default;
	Sink(DataSource* obj) : source(obj) {}

	void sendToStream(std::ostream& os) const;
	bool sendToStreamMax(std::ostream& os, int size) const;
public:
	virtual ~Sink() = default;

	void setDataSource(DataSource* newSource);

	virtual void flush() const = 0;
	virtual Sink* clone() const = 0;
};
