#include "BaseClasses.h"
#include <cassert>
#include "MyString.h"

void DataSource::validateState() const {
	if (!isValid()) {
		pointer = -1;
	}
}

bool DataSource::isValid() const {
	if (pointer >= 0 && pointer < data.getSize()) {
		return true;
	}
	return false;
}

bool DataSource::getSymbol(char& symbol) const {
	if (!isValid()) {
		return false;
	}

	symbol = data[pointer++];
	validateState();
	return true;
}

void DataSource::clear() const {
	pointer = 0; //clear state of pointer
}

void Stream::readFromStream(std::istream& is) {
	char ch;
	while (is.get(ch)) {
		data.pushBack(ch);
	}
}

void Filter::initContent(const DataSource& obj) {
	MyString temp;
	char ch;
	while (obj.getSymbol(ch)) {
		temp.pushBack(ch);
	}
	data = filter(std::move(temp));
}

void Sink::sendToStream(std::ostream& os) const {
	source->clear();
	char ch;
	while (source->getSymbol(ch)) {
		os << ch;
	}
}

bool Sink::sendToStreamMax(std::ostream& os, int size) const {
	char ch;
	for (int i = 1; i <= size; ++i) {
		if (!source->getSymbol(ch)) {
			return false;
		}
		os << ch;
	}
	return true;
}

void Sink::setDataSource(DataSource* newSource) {
	source = newSource;
}
