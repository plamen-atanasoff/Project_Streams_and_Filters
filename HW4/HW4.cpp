#include <iostream>
#include "StreamClasses.h"
#include "MyString.h"
#include "SinkClasses.h"
#include "FilterClasses.h"
#include "SequenceOfOperations.h"

int main() {
	try {
#if 0
		//Извличане на речник: чете файл, премахва пунктуация, добавя нови редове след всяка дума,
		//премахва дублиращите се редове, записва във файл.
		//Разделяне на файлове: чете един входен файл и го разделя на файлове не по-големи от К символа.
		FileStream fSt("text.txt");
		DynamicArray<Stream> streams;
		streams.add(fSt);

		PunctuationFilter pFil;
		AddNewRowAfterWordFilter anrawFil;
		RepeatingRowsFilter rrFil;
		LexicographicalComparisonOnRowsFilter lcorFil;
		DynamicArray<Filter> filters;
		filters.add(pFil);
		filters.add(anrawFil);
		filters.add(rrFil);
		filters.add(lcorFil);

		FileSink fSink("dictionary.txt");
		DynamicArray<Sink> sinks;
		sinks.add(fSink);

		SequenceOfOperations soo(streams, filters, sinks);

		FileStream fSt1("dictionary.txt");
		DynamicArray<Stream> streams1;
		streams1.add(fSt1);

		DynamicArray<Filter> filters1;

		FileSinkMaxK fSink1("archive.txt", 5);
		DynamicArray<Sink> sinks1;
		sinks1.add(fSink1);

		SequenceOfOperations soo1(streams1, filters1, sinks1);
#endif
#if 0
		//Брояч на думи във файлове: чете няколко файла, премахва пунктуация, 
		//слага всяка дума на отделен ред, премахва дадени думи, брои срещанията
		//и ги извежда на конзолата.
		FileStream fSt1("text1.txt");
		FileStream fSt2("text2.txt");
		FileStream fSt3("text3.txt");
		DynamicArray<Stream> streams1;
		streams1.add(fSt1);
		streams1.add(fSt2);
		streams1.add(fSt3);

		WordFilter wFil("Hello\n");
		GetRowsFilter grFil;
		PunctuationFilter pFil;
		AddNewRowAfterWordFilter anrawFil;
		DynamicArray<Filter> filters1;
		filters1.add(pFil);
		filters1.add(anrawFil);
		filters1.add(wFil);
		filters1.add(grFil); // 6

		ConsoleSink cSink;
		DynamicArray<Sink> sinks1;
		sinks1.add(cSink);

		SequenceOfOperations soo1(streams1, filters1, sinks1);
#endif
#if 0
		//Архивиране: чете множество файлове и ги записва в един изходен файл.
		FileStream fSt1("text1.txt");
		FileStream fSt2("text2.txt");
		FileStream fSt3("text3.txt");
		DynamicArray<Stream> streams2;
		streams2.add(fSt1);
		streams2.add(fSt2);
		streams2.add(fSt3);

		DynamicArray<Filter> filters2;

		FileSink fSink("archive.txt");
		DynamicArray<Sink> sinks2;
		sinks2.add(fSink);

		SequenceOfOperations soo1(streams2, filters2, sinks2);
#endif
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}
