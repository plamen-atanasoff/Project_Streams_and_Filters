#include "SequenceOfOperations.h"
#include "DynamicArray.hpp"
#include "SinkClasses.h"

void SequenceOfOperations::readData() {
	filteredData = readFromStreams(streams);
}

void SequenceOfOperations::filterData() {
	for (int i = 0; i < filters.getSize(); ++i) {
		filteredData = filters[i].filter(filteredData);
	}
}

void SequenceOfOperations::flushData() {
	ConstStream temp(filteredData);
	writeToStreams(sinks, temp);
}

SequenceOfOperations::SequenceOfOperations(DynamicArray<Stream>& streams, DynamicArray<Filter>& filters,
	DynamicArray<Sink>& sinks) : streams(streams), filters(filters), sinks(sinks) {
	readData();
	filterData();
	flushData();
}
