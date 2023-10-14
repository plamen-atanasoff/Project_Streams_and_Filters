#pragma once
#include "BaseClasses.h"
#include "DynamicArray.hpp"

class ConsoleSink : public Sink {
protected:
	virtual Sink* clone() const override {
		return DBG_NEW ConsoleSink(source);
	}
public:
	ConsoleSink(DataSource& obj);

	virtual void flush() const override;
};

class FileSink : public Sink {
protected:
	MyString fileName;

	virtual Sink* clone() const override {
		return DBG_NEW FileSink(source, fileName);
	}
public:
	FileSink(DataSource& obj, const MyString& fileName);

	virtual void flush() const override;
	void flushMax(int size) const;
};

class OutputStreamVector : public DynamicVector<Sink> {
private:
	DataSource& source;
public:
	OutputStreamVector(DataSource& source);

	void setSource(DataSource& newSource);
};

void writeToStreams(const OutputStreamVector& vec);
