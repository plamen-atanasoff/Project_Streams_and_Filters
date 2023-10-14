#include "SequenceOfOperations.h"
#include "DynamicArray.hpp"
#include "SinkClasses.h"

void SequenceOfOperations::readData() {
	filteredData = readFromStreams(streams);
	//std::cout << filteredData << std::endl;
}

void SequenceOfOperations::filterData() {
	for (int i = 0; i < filters.getSize(); ++i) {
		//std::cout << "\n--------------------------------------\n" << std::endl;
		filteredData = filters[i].filter(filteredData);
		//std::cout << filteredData << std::endl;
	}
}

void SequenceOfOperations::flushData() {
	ConstStream temp(filteredData);
	writeToStreams(sinks, temp);
}

SequenceOfOperations::SequenceOfOperations(DynamicVector<Stream>& streams, DynamicVector<Filter>& filters,
	DynamicVector<Sink>& sinks) : streams(streams), filters(filters), sinks(sinks) {
	readData();
	filterData();
	flushData();
}
