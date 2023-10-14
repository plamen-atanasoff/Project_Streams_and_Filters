#pragma once
#include "MyString.h"
#include "StreamClasses.h"

//Замяна на един низ с друг
class SequenceReplaceFilter : public Filter {
protected:
	MyString toReplace;
	MyString replaceWith;

	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return new SequenceReplaceFilter(*this);
	}
public:
	SequenceReplaceFilter(const DataSource& obj, const MyString& toReplace, const MyString& replaceWith) 
		: toReplace(toReplace), replaceWith(replaceWith) {
		Filter::initContent(obj);
	}
	SequenceReplaceFilter(const MyString& toReplace, const MyString& replaceWith) 
		: toReplace(toReplace), replaceWith(replaceWith) {}
};

//Премахване на даден низ от съдържанието
//Премахване на даден символ
//Премахване на нови редове
class WordFilter : public SequenceReplaceFilter {
protected:
	virtual Filter* clone() const override {
		return new WordFilter(*this);
	}
public:
	WordFilter(const DataSource& obj, const MyString& toRemove) : SequenceReplaceFilter(obj, toRemove, "") {}
	WordFilter(const MyString& toRemove) : SequenceReplaceFilter(toRemove, "") {}
};

//Премахване на цели редове, които съдържат даден низ
class RowFilter : public Filter {
protected:
	MyString toRemove;

	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return new RowFilter(*this);
	}
public:
	RowFilter(const DataSource& obj, const MyString& toRemove) : toRemove(toRemove) {
		Filter::initContent(obj);
	}
	RowFilter(const MyString& toRemove) : toRemove(toRemove) {}
};

//Премахване на пунктуация
class PunctuationFilter : public Filter {
protected:
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return new PunctuationFilter(*this);
	}
public:
	PunctuationFilter() = default;
	PunctuationFilter(const DataSource& obj) {
		Filter::initContent(obj);
	}
};

//Добавяне на нов ред след всяко изречение
class AddNewRowAfterSentenceFilter : public Filter {
protected:
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return new AddNewRowAfterSentenceFilter(*this);
	}
public:
	AddNewRowAfterSentenceFilter() = default;
	AddNewRowAfterSentenceFilter(const DataSource& obj) {
		Filter::initContent(obj);
	}
};

//Добавяне на нов ред след всяка дума
class AddNewRowAfterWordFilter : public Filter {
protected:
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return new AddNewRowAfterWordFilter(*this);
	}
public:
	AddNewRowAfterWordFilter() = default;
	AddNewRowAfterWordFilter(const DataSource& obj) {
		Filter::initContent(obj);
	}
};

//Добавяне на нов ред, така че всеки ред да не е повече от К символа, без да се разделят думи ако е възможно
class AddNewRowAfterKSymbolsFilter : public Filter {
protected:
	int K;
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return new AddNewRowAfterKSymbolsFilter(*this);
	}
public:
	AddNewRowAfterKSymbolsFilter(int K) : K(K) {
		if (K <= 0) {
			throw std::invalid_argument("K must be positive!");
		}
	}
	AddNewRowAfterKSymbolsFilter(const DataSource& obj, int K) : K(K) {
		if (K <= 0) {
			throw std::invalid_argument("K must be positive!");
		}
		Filter::initContent(obj);
	}
};

//Лексикографско сортиране на всички редове
class LexicographicalComparisonOnRowsFilter : public Filter {
protected:
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return new LexicographicalComparisonOnRowsFilter(*this);
	}
public:
	LexicographicalComparisonOnRowsFilter() = default;
	LexicographicalComparisonOnRowsFilter(const DataSource& obj) {
		Filter::initContent(obj);
	}
};

//Премахване на дублиращите се редове
class RepeatingRowsFilter : public Filter {
protected:
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return new RepeatingRowsFilter(*this);
	}
public:
	RepeatingRowsFilter() = default;
	RepeatingRowsFilter(const DataSource& obj) {
		Filter::initContent(obj);
	}
};

//Извежда броя редове във входните данни, броят става новото изходно съдържание
class GetRowsFilter : public Filter {
protected:
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return new GetRowsFilter(*this);
	}
public:
	GetRowsFilter() = default;
	GetRowsFilter(const DataSource& obj) {
		Filter::initContent(obj);
	}
};

//Извежда броя символи във входните данни, броят става новото изходно съдържание
class GetSymbolsFilter : public Filter {
protected:
	virtual MyString filter(const MyString& toFilter) const override;
	virtual Filter* clone() const override {
		return new GetSymbolsFilter(*this);
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
