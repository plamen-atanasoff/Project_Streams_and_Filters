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

int main(){
	{
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

		//ConstStream cSt("newTesting");
		//int sinksCount = 3;
		//ConsoleSink s(cSt);
		//FileSink fSink1(cSt, "fSink1.txt");
		//FileSink fSink2(cSt, "fSink2.txt");
		//OutputStreamVector vec1(cSt);
		//vec1.add(s);
		//vec1.add(fSink1);
		//vec1.add(fSink2);
		//writeToStreams(vec1);
		//fSink1.flushMax(1);

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
		//AddNewRowAfterKSymbolsFilter anraksFil(cSt4, 10); // try to fix when a word would fit by itself but not with the space
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

		ConsoleStream st;
		ConstStream cSt3("*Hello there.\n*Hello there.\nHow are* you?\nI am good!\n*Hello there.\nHow are* you?\nTesting***\n");
		FileStream fSt("text.txt");
		DynamicVector<Stream> vec;
		vec.add(st);
		vec.add(cSt3);
		vec.add(fSt);

		RepeatingRowsFilter rrFil(cSt3);
		cSt3.clear();
		WordFilter wFil(cSt3, '*');
		cSt3.clear();
		SequenceReplaceFilter srFil(cSt3, "Hello", "Privet");

		DynamicVector<Filter> vecFil;
		vecFil.add(rrFil);
		vecFil.add(wFil);
		vecFil.add(srFil);

		ConstStream cSt("newTesting");
		ConsoleSink s(cSt);
		FileSink fSink1(cSt, "fSink1.txt");
		FileSink fSink2(cSt, "fSink2.txt");
		OutputStreamVector vec1(cSt);
		vec1.add(s);
		vec1.add(fSink1);
		vec1.add(fSink2);

		SequenceOfOperations soo(vec, vecFil, vec1);
	}
	_CrtDumpMemoryLeaks();
}
