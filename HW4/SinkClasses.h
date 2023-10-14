#pragma once
#include "BaseClasses.h"
#include "DynamicArray.hpp"

class ConsoleSink : public Sink {
protected:
	virtual Sink* clone() const override {
		return DBG_NEW ConsoleSink(*source);
	}
public:
	ConsoleSink() = default;
	ConsoleSink(DataSource& obj);

	virtual void flush() const override;
};

class FileSink : public Sink {
protected:
	MyString fileName;

	virtual Sink* clone() const override {
		return DBG_NEW FileSink(*source, fileName);
	}
public:
	FileSink(const MyString& fileName);
	FileSink(DataSource& obj, const MyString& fileName);

	virtual void flush() const override;
};

class FileSinkMaxK : public Sink {
protected:
	MyString fileName;
	int K;

	virtual Sink* clone() const override {
		return DBG_NEW FileSinkMaxK(*source, fileName, K);
	}
public:
	FileSinkMaxK(const MyString& fileName, int maxChars);
	FileSinkMaxK(DataSource& obj, const MyString& fileName, int maxChars);

	virtual void flush() const override;
};

void writeToStreams(const DynamicVector<Sink>& vec);
void writeToStreams(DynamicVector<Sink>& vec, DataSource& source);
