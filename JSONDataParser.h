// JSONDataParser.h

#ifndef _JSONDATAPARSER_h
#define _JSONDATAPARSER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class JSONDataParser_ {
public:

	JSONDataParser_() {};
	JSONDataParser_(String* tokens, byte nTokens, byte* maxLengthDataSize);
	~JSONDataParser_();

	void initParser(String* tokens, byte nTokens, byte* maxLengthDataSize);

	void clearMemory();

	void parseNextChar(char &c);
	byte* getLengthOfDataResults();
	String*** getResultData();

private:

	String* tokensForFind;
	byte* resultLengths;
	byte* maxDataLengths;
	int* charCounters;
	String*** results;
	int numberOfTokens;

	int nOfTokenForReadData = -1;
	String tokenEnd = "\":"; // ":
	char endOfDataChar = -1;

};

#endif

