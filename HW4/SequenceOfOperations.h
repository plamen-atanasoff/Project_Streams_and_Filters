#pragma once
#include "MyString.h"
#include "StreamClasses.h"
#include "FilterClasses.h"
#include "SinkClasses.h"
#include "BaseClasses.h"
#include "DynamicArray.hpp"

class SequenceOfOperations {
private:
	MyString filteredData;
	DynamicVector<Stream>& streams;
	DynamicVector<Filter>& filters;
	DynamicVector<Sink>& sinks;

	void readData();
	void filterData();
	void flushData();
public:
	SequenceOfOperations(DynamicVector<Stream>& streams, DynamicVector<Filter>& filters, DynamicVector<Sink>& sinks);
	SequenceOfOperations(const SequenceOfOperations& other) = delete;
	SequenceOfOperations operator=(const SequenceOfOperations& other) = delete;
};
