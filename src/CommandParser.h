/*
 * CommandParser.h
 */
#ifndef COMMANDPARSER_H_
#define COMMANDPARSER_H_

#include <string>
#include <vector>
#include "KeywordMap.h"
#include "baseapi.h"
using namespace std;
using namespace tesseract;

class CommandParser {
public:
	CommandParser();
	virtual ~CommandParser();
	Commands parse(string commandChar, vector<string> &result);
	Commands getCommandID(string commandString);
	bool getPageSegMode(string stPSM, PageSegMode* target);
	bool getPSMString(PageSegMode psm, string* target);
	bool getOcrEngineMode(string stOEM, OcrEngineMode* target);
	bool getOEMString(OcrEngineMode oem, string* target);
private:
	void split(string inputString, char splitChar, vector<string> & output);
	map<string, PageSegMode> psmStrings;
	map<string, OcrEngineMode> oemStrings;
};

#endif /* COMMANDPARSER_H_ */
