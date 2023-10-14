#pragma once
#include "MyString.h"
#include "StreamClasses.h"

class SequenceReplaceFilter : public Filter {
protected:
	MyString toReplace;
	MyString replaceWith;

	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return DBG_NEW SequenceReplaceFilter(*this);
	}
public:
	SequenceReplaceFilter(const DataSource& obj, const MyString& toReplace, const MyString& replaceWith) 
		: toReplace(toReplace), replaceWith(replaceWith) {
		Filter::initContent(obj);
	}
	SequenceReplaceFilter(const MyString& toReplace, const MyString& replaceWith) 
		: toReplace(toReplace), replaceWith(replaceWith) {}
};

class WordFilter : public SequenceReplaceFilter {
protected:
	virtual Filter* clone() const override {
		return DBG_NEW WordFilter(*this);
	}
public:
	WordFilter(const DataSource& obj, const MyString& toRemove) : SequenceReplaceFilter(obj, toRemove, "") {}
	WordFilter(const MyString& toRemove) : SequenceReplaceFilter(toRemove, "") {}
};

class RowFilter : public Filter {
protected:
	MyString toRemove;

	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return DBG_NEW RowFilter(*this);
	}
public:
	RowFilter(const DataSource& obj, const MyString& toRemove) : toRemove(toRemove) {
		Filter::initContent(obj);
	}
	RowFilter(const MyString& toRemove) : toRemove(toRemove) {}
};

class PunctuationFilter : public Filter {
protected:
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return DBG_NEW PunctuationFilter(*this);
	}
public:
	PunctuationFilter() = default;
	PunctuationFilter(const DataSource& obj) {
		Filter::initContent(obj);
	}
};

class AddNewRowAfterSentenceFilter : public Filter {
protected:
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return DBG_NEW AddNewRowAfterSentenceFilter(*this);
	}
public:
	AddNewRowAfterSentenceFilter() = default;
	AddNewRowAfterSentenceFilter(const DataSource& obj);
};

class AddNewRowAfterWordFilter : public Filter {
protected:
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return DBG_NEW AddNewRowAfterWordFilter(*this);
	}
public:
	AddNewRowAfterWordFilter() = default;
	AddNewRowAfterWordFilter(const DataSource& obj);
};

class AddNewRowAfterKSymbolsFilter : public Filter {
protected:
	int K;
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return DBG_NEW AddNewRowAfterKSymbolsFilter(*this);
	}
public:
	AddNewRowAfterKSymbolsFilter(int K);
	AddNewRowAfterKSymbolsFilter(const DataSource& obj, int K);
};

class LexicographicalComparisonOnRowsFilter : public Filter {
protected:
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return DBG_NEW LexicographicalComparisonOnRowsFilter(*this);
	}
public:
	LexicographicalComparisonOnRowsFilter() = default;
	LexicographicalComparisonOnRowsFilter(const DataSource& obj) {
		Filter::initContent(obj);
	}
};

class RepeatingRowsFilter : public Filter {
protected:
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return DBG_NEW RepeatingRowsFilter(*this);
	}
public:
	RepeatingRowsFilter() = default;
	RepeatingRowsFilter(const DataSource& obj) {
		Filter::initContent(obj);
	}
};

class GetRowsFilter : public Filter {
protected:
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return DBG_NEW GetRowsFilter(*this);
	}
public:
	GetRowsFilter() = default;
	GetRowsFilter(const DataSource& obj) {
		Filter::initContent(obj);
	}
};

class GetSymbolsFilter : public Filter {
protected:
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return DBG_NEW GetSymbolsFilter(*this);
	}
public:
	GetSymbolsFilter() = default;
	GetSymbolsFilter(const DataSource& obj) {
		Filter::initContent(obj);
	}
};

int getSizeOfRow(const MyString& str, int startPosRow);
int* getRows(const MyString& str);
int getRowsCount(const MyString& str);
