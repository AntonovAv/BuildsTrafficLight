// 
// 
// 

#include "JSONDataParser.h"

JSONDataParser_::~JSONDataParser_() {
	clearMemory();
}

JSONDataParser_::JSONDataParser_(String* tokens, byte nTokens, byte* maxLengthDataSize) {
	initParser(tokens, nTokens, maxLengthDataSize);
}

void JSONDataParser_::initParser(String *tokens, byte nTokens, byte* maxLengthDataSize){

	numberOfTokens = nTokens;
	tokensForFind = new String[nTokens];

	maxDataLengths = maxLengthDataSize;
	resultLengths = new byte[nTokens];
	charCounters = new int[nTokens];

	results = new String**[nTokens];
	// init values
	for (int i = 0; i < nTokens; i++) {
		resultLengths[i] = 0;
		charCounters[i] = 0;
		tokensForFind[i] = tokens[i] + tokenEnd;
		results[i] = new String*[maxLengthDataSize[i]];
		for (int j = 0; j < maxLengthDataSize[i]; j++) {
			results[i][j] = 0;
		}
	}
}

void JSONDataParser_::clearMemory() {
	for (int i = 0; i < numberOfTokens; i++) {
		for (int j = 0; j < maxDataLengths[i]; j++) {
			if (results[i][j] != 0) {
				delete results[i][j];
			}
		}
		delete[] results[i];
	}
	delete[] results;

	delete[] tokensForFind;
	delete[] resultLengths;
	delete[] charCounters;
}

void JSONDataParser_::parseNextChar(char &c) {
	for (int i = 0; i < numberOfTokens; i++) {
		if (resultLengths[i] <= maxDataLengths[i]) { // if data enought read - escape parsing
			if (i == nOfTokenForReadData) { // read data for current token
				if (endOfDataChar == -1) { // if not read end of data char(first char after token)
					switch (c) {
					case '"':
						endOfDataChar = '"';
						return;
					case '{':
						endOfDataChar = '}';
						return;
					case '[':
						endOfDataChar = ']';
						return;
					default:
						endOfDataChar = ',';
						break; // go to read char to data
					}
				}
				if (c != endOfDataChar) {
					charCounters[i] += 1;
					(*results[i][resultLengths[i]]) += c; // add char to data
					
				}
				else {
					resultLengths[i] += 1;
					endOfDataChar = -1;
					nOfTokenForReadData = -1;
				}
			}
			else {
				if (tokensForFind[i].charAt(charCounters[i]) == c) {
					charCounters[i] += 1;

					if (tokensForFind[i].length() == charCounters[i]) {
						nOfTokenForReadData = i; // current token ready for read data
						charCounters[i] = 0;
						results[i][resultLengths[i]] = new String;
					}
				}
				else {
					charCounters[i] = 0;
					if (tokensForFind[i].charAt(0) == c) {
						charCounters[i] += 1;
					}
				}
			}
		}
	}
}

byte* JSONDataParser_::getLengthOfDataResults() {
	return resultLengths;
}

String***  JSONDataParser_::getResultData() {
	return results;
}