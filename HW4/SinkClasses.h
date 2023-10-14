#pragma once
#include "BaseClasses.h"
#include "DynamicArray.hpp"
#include <exception>

class ConsoleSink : public Sink {
protected:
	virtual Sink* clone() const override {
		return new ConsoleSink(*source);
	}
public:
	ConsoleSink() = default;
	ConsoleSink(DataSource& obj) : Sink(&obj) {}

	virtual void flush() const override;
};

class FileSink : public Sink {
protected:
	MyString fileName;

	virtual Sink* clone() const override {
		return new FileSink(*source, fileName);
	}
public:
	FileSink(const MyString& fileName) : fileName(fileName) {}
	FileSink(DataSource& obj, const MyString& fileName) : Sink(&obj), fileName(fileName) {}

	virtual void flush() const override;
};

//Трябва да може да се записва съдържанието в няколко изходни файла. 
//Данните се записват във файл и при достигане на подаден максимален размер К, се създава нов файл. 
class FileSinkMaxK : public Sink {
protected:
	MyString fileName;
	int K;

	virtual Sink* clone() const override {
		return new FileSinkMaxK(*source, fileName, K);
	}
public:
	FileSinkMaxK(const MyString& fileName, int maxChars) : fileName(fileName), K(maxChars) {}
	FileSinkMaxK(DataSource& obj, const MyString& fileName, int maxChars)
		: Sink(&obj), fileName(fileName), K(maxChars) {
		if (maxChars <= 0) {
			throw std::invalid_argument("maxChars must be positive!");
		}
	}
	virtual void flush() const override;
};

//Трябва да може да се записва съдържанието в няколко изхода като се копират данните във всеки изход.
void writeToStreams(const DynamicArray<Sink>& vec);
void writeToStreams(DynamicArray<Sink>& vec, DataSource& source);
