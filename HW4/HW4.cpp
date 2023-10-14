#include <iostream>
#include "StreamClasses.h"
#include "MyString.h"
#include "SinkClasses.h"
#include "FilterClasses.h"
#include "SequenceOfOperations.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

int main() {
	try {
		//Извличане на речник: чете файл, премахва пунктуация, добавя нови редове след всяка дума,
		//премахва дублиращите се редове, записва във файл
#if 1
		FileStream fSt("text.txt");
		DynamicVector<Stream> streams;
		streams.add(fSt);

		PunctuationFilter pFil;
		AddNewRowAfterWordFilter anrawFil;
		RepeatingRowsFilter rrFil;
		LexicographicalComparisonOnRowsFilter lcorFil;
		DynamicVector<Filter> filters;
		filters.add(pFil);
		filters.add(anrawFil);
		filters.add(rrFil);
		filters.add(lcorFil);

		FileSink fSink("dictionary.txt");
		DynamicVector<Sink> sinks;
		sinks.add(fSink);

		SequenceOfOperations soo(streams, filters, sinks);
#endif
		//Брояч на думи във файлове: чете няколко файла, премахва пунктуация, 
		//слага всяка дума на отделен ред, премахва дадени думи, брои срещанията
		//и ги извежда на конзолата.
#if 0
		FileStream fSt1("text1.txt");
		FileStream fSt2("text2.txt");
		FileStream fSt3("text3.txt");
		DynamicVector<Stream> streams1;
		streams1.add(fSt1);
		streams1.add(fSt2);
		streams1.add(fSt3);

		WordFilter wFil("Hello\n");
		GetRowsFilter grFil;
		PunctuationFilter pFil;
		AddNewRowAfterWordFilter anrawFil;
		DynamicVector<Filter> filters1;
		filters1.add(pFil);
		filters1.add(anrawFil);
		filters1.add(wFil);
		filters1.add(grFil); // 6

		ConsoleSink cSink(nullptr);
		DynamicVector<Sink> sinks1;
		sinks1.add(cSink);

		SequenceOfOperations soo1(streams1, filters1, sinks1);
#endif
		//Архивиране: чете множество файлове и ги записва в един изходен файл
#if 0
		FileStream fSt1("text1.txt");
		FileStream fSt2("text2.txt");
		FileStream fSt3("text3.txt");
		DynamicVector<Stream> streams2;
		streams2.add(fSt1);
		streams2.add(fSt2);
		streams2.add(fSt3);

		DynamicVector<Filter> filters2;

		FileSink fSink(nullptr, "archive.txt");
		DynamicVector<Sink> sinks2;
		sinks2.add(fSink);

		SequenceOfOperations soo1(streams2, filters2, sinks2);
#endif
		//Разделяне на файлове: чете един входен файл и го разделя на файлове не по-големи от К символа
#if 0
		FileStream fSt("text.txt");
		DynamicVector<Stream> streams3;
		streams3.add(fSt);

		DynamicVector<Filter> filters3;

		FileSinkMaxK fSink1(nullptr, "archive.txt", 25);
		DynamicVector<Sink> sinks3;
		sinks3.add(fSink1);

		SequenceOfOperations soo1(streams3, filters3, sinks3);
#endif
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}

#if 0
int main(){
	{
		//int streamsCount = 3;
		//ConsoleStream st;
		//ConstStream cSt("testing2");
		//FileStream fSt("text.txt");
		//DynamicVector<Stream> vec;
		//vec.add(st);
		//vec.add(cSt);
		//vec.add(fSt);
		//MyString result = readFromStreams(vec);
		//std::cout << result;

		//ConstStream cSt("newTesting123");
		//int sinksCount = 3;
		//ConsoleSink s;
		//FileSink fSink1("fSink1.txt");
		//FileSinkMaxK fSink2("fSink2.txt", 5);
		//DynamicVector<Sink> vec1;
		//vec1.add(s);
		//vec1.add(fSink1);
		//vec1.add(fSink2);
		//writeToStreams(vec1, cSt);

		//ConstStream cSt2("nightlife\notherlife\nMy computer\nHello there\n12door life something\nEnding\n");
		////ConstStream cSt2("Hello there\n12door life something");
		//RowFilter rFil(cSt2, "life");
		//ConsoleSink s2(rFil);
		//s2.flush();

		//ConstStream cSt3("\neHeeeeello there\n12door life somethinge\n");
		//WordFilter wFil(cSt3, 'e');
		//ConsoleSink s3(wFil);
		//s3.flush();

		//ConstStream cSt4("nightlife\notherlifelife\nMy computer\nHello there\n12door life something\nEnding\n");
		//SequenceReplaceFilter srFil(cSt4, "life", "monster");
		//ConsoleSink s3(srFil);
		//s3.flush();

		//ConstStream cSt4("nightlife...\notherlife*/life\nMy comp!!!?uter\nHello there\n12do:''\"\"or life something\nEnding\n");
		//PunctuationFilter pFil(cSt4);
		//ConsoleSink s3(pFil);
		//s3.flush();

		//ConstStream cSt4("Hello there.Why did you do this?Stop!");
		//AddNewRowAfterSentenceFilter anrasFil(cSt4);
		//ConsoleSink s3(anrasFil);
		//s3.flush();

		//ConstStream cSt4("Hello there. Why did you do this? Stop it!");
		//AddNewRowAfterWordFilter anrawFil(cSt4);
		//ConsoleSink s3(anrawFil);
		//s3.flush();

		//ConstStream cSt4("hi hi bye there. Why dsadasdsadasdaid you do this? Stop it!");
		//AddNewRowAfterKSymbolsFilter anraksFil(cSt4, 10);
		//ConsoleSink s3(anraksFil);
		//s3.flush();

		//ConstStream cSt3("\neHeeeeello there\n\n12door life somethinge\n");
		//WordFilter wFil(cSt3, '\n');
		//ConsoleSink s3(wFil);
		//s3.flush();

		//ConstStream cSt3("eHeeeeello there.\nTesting!\n12door life somethinge.\n");
		//LexicographicalComparisonOnRowsFilter lcorFil(cSt3);
		//ConsoleSink s3(lcorFil);
		//s3.flush();

		//ConstStream cSt3("Hello there.\nHello there.\nHow are you?\nI am good!\nHello there.\nHow are you?\nTesting");
		//RepeatingRowsFilter rrFil(cSt3);
		//ConsoleSink s3(rrFil);
		//s3.flush();

		//ConstStream cSt3("Hello there.\nHello there.\nHow are you?\nI am good!\nHello there.\nHow are you?\nTesting");
		//GetRowsFilter grFil(cSt3);
		//cSt3.clear();
		//GetSymbolsFilter gsFil(cSt3);
		//ConsoleSink s3(grFil);
		//s3.flush();
		//ConsoleSink s4(gsFil);
		//s4.flush();

		//int streamsCount = 3;
		//ConsoleStream st;
		//ConstStream cSt("testing2");
		//FileStream fSt("text.txt");
		//InputStreamVector vec;
		//vec.add(st);
		//vec.add(cSt);
		//vec.add(fSt);
		//MyString result = readFromStreams(vec);
		//std::cout << result;

		//ConsoleStream st;
		//ConstStream cSt3("*Hello there.\n*Hello there.\nHow are* you?\nI am good!\n*Hello there.\nHow are* you?\nTesting***\n");
		//FileStream fSt("text.txt");
		//DynamicVector<Stream> vec;
		//vec.add(st);
		//vec.add(cSt3);
		//vec.add(fSt);

		//RepeatingRowsFilter rrFil(cSt3);
		//cSt3.clear();
		//WordFilter wFil(cSt3, '*');
		//cSt3.clear();
		//SequenceReplaceFilter srFil(cSt3, "Hello", "Privet");

		//DynamicVector<Filter> vecFil;
		//vecFil.add(rrFil);
		//vecFil.add(wFil);
		//vecFil.add(srFil);

		//ConstStream cSt("newTesting");
		//ConsoleSink s(cSt);
		//FileSink fSink1(cSt, "fSink1.txt");
		//FileSink fSink2(cSt, "fSink2.txt");
		//OutputStreamVector vec1(cSt);
		//vec1.add(s);
		//vec1.add(fSink1);
		//vec1.add(fSink2);

		//SequenceOfOperations soo(vec, vecFil, vec1);
	}
	_CrtDumpMemoryLeaks();
}
#endif