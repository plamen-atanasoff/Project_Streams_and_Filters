#include "FilterClasses.h"
#include "StreamClasses.h"
#include <cassert>
#include <cctype>
#include <utility>
#include <exception>

MyString SequenceReplaceFilter::filter(const MyString& toFilter) const {
	int toFilterSize = toFilter.getSize();
	int toReplaceSize = toReplace.getSize();
	MyString res(toFilterSize);
	for (int i = 0; i < toFilterSize; ++i) {
		while (i <= toFilterSize - toReplaceSize && toFilter.substringExists(toReplace, i, i + toReplaceSize)) {
			res.append(replaceWith);
			i += toReplaceSize;
		}
		if (i == toFilterSize) {
			return res;
		}
		res.pushBack(toFilter[i]);
	}
	return res;
}

MyString RowFilter::filter(const MyString& toFilter) const {
	int toFilterSize = toFilter.getSize();
	MyString res(toFilterSize);
	int currStartPos = 0;
	for (int i = 0; i < toFilterSize; ++i) {
		if (toFilter[i] == '\n') {
			if (!toFilter.substringExists(toRemove, currStartPos, i)) {
				res.append(toFilter.getSubstring(currStartPos, i - currStartPos + 1));
			}
			currStartPos = i + 1;
		}
	}
	if (currStartPos == toFilterSize) { //all data is filtered
		return res;
	} //data does not end with \n and last row needs to be appended
	else if (!toFilter.substringExists(toRemove, currStartPos, toFilterSize)) {
		res.append(toFilter.getSubstring(currStartPos, toFilterSize - currStartPos));
	}
	return res;
}

MyString PunctuationFilter::filter(const MyString& toFilter) const {
	int toFilterSize = toFilter.getSize();
	MyString res(toFilterSize);
	for (int i = 0; i < toFilterSize; ++i) {
		if (!ispunct(toFilter[i])) {
			res.pushBack(toFilter[i]);
		}
	}
	return res;
}

MyString AddNewRowAfterSentenceFilter::filter(const MyString& toFilter) const {
	MyString res(toFilter.getSize());
	for (int i = 0; i < toFilter.getSize(); ++i) {
		res.pushBack(toFilter[i]);
		if (toFilter[i] == '.' || toFilter[i] == '!' || toFilter[i] == '?') {
			res.pushBack('\n');
		}
	}
	return res;
}

MyString AddNewRowAfterWordFilter::filter(const MyString& toFilter) const {
	MyString res(toFilter.getSize());
	for (int i = 0; i < toFilter.getSize(); ++i) {
		if (toFilter[i] == ' ') {
			res.pushBack('\n');
		}
		else {
			res.pushBack(toFilter[i]);
		}
	}
	return res;
}

MyString AddNewRowAfterKSymbolsFilter::filter(const MyString& toFilter) const {
	MyString res(toFilter.getSize());
	const char* begPtr = toFilter.getC_str();
	const char* currPtr = nullptr;
	int remainingSymbols = K;
	while (currPtr = strchr(begPtr, ' ')) {
		int lenghtOfCurrWord = static_cast<int>(currPtr - begPtr);
		if (remainingSymbols > lenghtOfCurrWord) {
			res.append(toFilter.getSubstring(static_cast<int>(begPtr - toFilter.getC_str()), lenghtOfCurrWord));
			res.pushBack(' ');
			remainingSymbols -= lenghtOfCurrWord + 1;
			begPtr += static_cast<size_t>(lenghtOfCurrWord) + 1;
		}
		else if (remainingSymbols == lenghtOfCurrWord) {
			res.append(toFilter.getSubstring(static_cast<int>(begPtr - toFilter.getC_str()), lenghtOfCurrWord));
			res.pushBack('\n');
			res.pushBack(' ');
			remainingSymbols = K - 1;
			begPtr += static_cast<size_t>(lenghtOfCurrWord) + 1;
		}
		else {
			if (lenghtOfCurrWord < K) {
				res.pushBack('\n');
				res.append(toFilter.getSubstring(static_cast<int>(begPtr - toFilter.getC_str()), lenghtOfCurrWord));
				res.pushBack(' ');
				remainingSymbols = K - (lenghtOfCurrWord + 1);
				begPtr += static_cast<size_t>(lenghtOfCurrWord) + 1;
			}
			else if (lenghtOfCurrWord == K) {
				res.pushBack('\n');
				res.append(toFilter.getSubstring(static_cast<int>(begPtr - toFilter.getC_str()), lenghtOfCurrWord));
				res.pushBack('\n');
				res.pushBack(' ');
				remainingSymbols = K - 1;
				begPtr += static_cast<size_t>(lenghtOfCurrWord) + 1;
			}
			else {
				while (lenghtOfCurrWord > K) {
					lenghtOfCurrWord = static_cast<int>(currPtr - begPtr);
					int temp = lenghtOfCurrWord > K ? remainingSymbols : lenghtOfCurrWord;
					res.append(toFilter.getSubstring(static_cast<int>(begPtr - toFilter.getC_str()), temp));
					if (temp == remainingSymbols) {
						res.pushBack('\n');
						remainingSymbols = K;
					}
					else {
						res.pushBack(' ');
						remainingSymbols -= temp + 1;
						begPtr++;
					}
					begPtr += temp;
				}
			}
		}
		if (remainingSymbols == 0) {
			res.pushBack('\n');
			remainingSymbols = K;
		}
	}

	const char* endPtr = toFilter.getC_str() + toFilter.getSize();
	while (begPtr < endPtr) {
		int temp = static_cast<int>(endPtr - begPtr > K ? K : endPtr - begPtr);
		res.pushBack('\n');
		res.append(toFilter.getSubstring(static_cast<int>(begPtr - toFilter.getC_str()), temp));
		res.pushBack('\n');
		begPtr += temp;
	}
	return res;
}

MyString LexicographicalComparisonOnRowsFilter::filter(const MyString& toFilter) const {
	int toFilterSize = toFilter.getSize();
	MyString res(toFilterSize);

	int rowsCount = getRowsCount(toFilter);
	int* rows = getRows(toFilter);
	const char* begPtr = toFilter.getC_str();
	//sorting using selection sort
	for (int i = 0; i < rowsCount - 1; ++i) {
		int currentSmallestRowInd = i;
		for (int j = i + 1; j < rowsCount; ++j) {
			if (strcmp(begPtr + rows[currentSmallestRowInd], begPtr + rows[j]) > 0) {
				currentSmallestRowInd = j;
			}
		}
		res.append(toFilter.getSubstring(rows[currentSmallestRowInd], getSizeOfRow(toFilter, rows[currentSmallestRowInd])));
		std::swap(rows[i], rows[currentSmallestRowInd]);
	}
	res.append(toFilter.getSubstring(rows[rowsCount - 1], getSizeOfRow(toFilter, rows[rowsCount - 1])));
	delete[] rows;

	return res;
}

MyString RepeatingRowsFilter::filter(const MyString& toFilter) const {
	int toFilterSize = toFilter.getSize();
	MyString res(toFilterSize);

	int rowsCount = getRowsCount(toFilter);
	int* rows = getRows(toFilter);
	const char* begPtr = toFilter.getC_str();
	for (int i = 0; i < rowsCount - 1; ++i) {
		bool exists = false;
		// check if every row before the current row is unique
		for (int j = 0; j < i; ++j) {
			if (strncmp(begPtr + rows[i], begPtr + rows[j], rows[i + 1] - rows[i]) == 0) {
				exists = true;
				break;
			}
		}
		if (!exists) {
			res.append(toFilter.getSubstring(rows[i], getSizeOfRow(toFilter, rows[i])));
		}
	}
	//check if the last row is unique
	bool exists = false;
	for (int i = 0; i < rowsCount - 1; ++i) {
		if (strncmp(begPtr + rows[i], begPtr + rows[rowsCount - 1], rows[i + 1] - rows[i] - 1) == 0) {
			exists = true;
			break;
		}
	}
	if (!exists) {
		res.append(toFilter.getSubstring(rows[rowsCount - 1], getSizeOfRow(toFilter, rows[rowsCount - 1])));
	}
	delete[] rows;

	return res;
}

MyString GetRowsFilter::filter(const MyString& toFilter) const {
	return to_MyString(getRowsCount(toFilter));
}

MyString GetSymbolsFilter::filter(const MyString& toFilter) const {
	return to_MyString(toFilter.getSize());
}

int getSizeOfRow(const MyString& str, int startPosRow) {
	for (int i = startPosRow; i < str.getSize(); ++i) {
		if (str[i] == '\n') {
			return i - startPosRow + 1;
		}
	}
	return str.getSize() - startPosRow; // there is no '\n' at the end of the string
}

int* getRows(const MyString& str) {
	int rowsCount = getRowsCount(str);

	// find rows' starting indices
	int* rows = new int[rowsCount];
	rows[0] = 0;
	for (int currSentenceStartInd = 0, arrIndex = 1; currSentenceStartInd < str.getSize() - 1; ++currSentenceStartInd) {
		if (str[currSentenceStartInd] == '\n') {
			rows[arrIndex++] = currSentenceStartInd + 1;
		}
	}
	return rows;
}

int getRowsCount(const MyString& str) {
	if (str.getSize() == 0) {
		return 0;
	}

	int count = 1;
	const char* beg = str.getC_str();
	while (const char* curr = strchr(beg, '\n')) {
		count++;
		beg = curr + 1;
	}
	if (str[str.getSize() - 1] == '\n') { //check if '\n' is at the end
		count--;
	}
	return count;
}