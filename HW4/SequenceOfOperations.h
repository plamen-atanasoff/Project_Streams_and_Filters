#pragma once
#include "MyString.h"
#include "StreamClasses.h"
#include "FilterClasses.h"
#include "SinkClasses.h"
#include "BaseClasses.h"
#include "DynamicArray.hpp"

//Трябва да има начин да се групират вход, множество трансформации и изход в поредици от задачи.
class SequenceOfOperations {
private:
	MyString filteredData;
	DynamicArray<Stream>& streams;
	DynamicArray<Filter>& filters;
	DynamicArray<Sink>& sinks;

	void readData();
	void filterData();
	void flushData();
public:
	SequenceOfOperations(DynamicArray<Stream>& streams, DynamicArray<Filter>& filters, DynamicArray<Sink>& sinks);
	SequenceOfOperations(const SequenceOfOperations& other) = delete;
	SequenceOfOperations operator=(const SequenceOfOperations& other) = delete;
};
