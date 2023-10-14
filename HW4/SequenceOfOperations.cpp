#include "SequenceOfOperations.h"
#include "DynamicArray.hpp"

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
	sinks.setSource(temp);
	writeToStreams(sinks);
}

SequenceOfOperations::SequenceOfOperations(DynamicVector<Stream>& streams, DynamicVector<Filter>& filters,
	OutputStreamVector& sinks) : streams(streams), filters(filters), sinks(sinks) {
	readData();
	filterData();
	flushData();
}
