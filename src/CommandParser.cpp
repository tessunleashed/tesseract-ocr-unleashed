/*
 * CommandParser.cpp
 * Offers functions for command parsing.
 */

#include "stdafx.h"
#include "CommandParser.h"
#include "KeywordMap.h"
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
using namespace tesseract;

CommandParser::CommandParser() {
	psmStrings["PSM_OSD_ONLY"] = PSM_OSD_ONLY;
	psmStrings["PSM_AUTO_OSD"] = PSM_AUTO_OSD;
	psmStrings["PSM_AUTO_ONLY"] = PSM_AUTO_ONLY;
	psmStrings["PSM_AUTO"] = PSM_AUTO;
	psmStrings["PSM_SINGLE_COLUMN"] = PSM_SINGLE_COLUMN;
	psmStrings["PSM_SINGLE_BLOCK_VERT_TEXT"] = PSM_SINGLE_BLOCK_VERT_TEXT;
	psmStrings["PSM_SINGLE_BLOCK"] = PSM_SINGLE_BLOCK;
	psmStrings["PSM_SINGLE_LINE"] = PSM_SINGLE_LINE;
	psmStrings["PSM_SINGLE_WORD"] = PSM_SINGLE_WORD;
	psmStrings["PSM_CIRCLE_WORD"] = PSM_CIRCLE_WORD;
	psmStrings["PSM_SINGLE_CHAR"] = PSM_SINGLE_CHAR;
	psmStrings["PSM_COUNT"] = PSM_COUNT;

	oemStrings["OEM_TESSERACT_ONLY"] = OEM_TESSERACT_ONLY;
	oemStrings["OEM_CUBE_ONLY"] = OEM_CUBE_ONLY;
	oemStrings["OEM_TESSERACT_CUBE_COMBINED"] = OEM_TESSERACT_CUBE_COMBINED;
	oemStrings["OEM_DEFAULT"] = OEM_DEFAULT;
}

CommandParser::~CommandParser() {
	psmStrings.clear();
	oemStrings.clear();
}

/*
 * Parses command input into an array containing the command name and
 * the parameters as array entrys in order to call tesseract commands from it.
 * returns negative number if error occured, and 0 or positive number
 *  if successfully parsed.
 */
Commands CommandParser::parse(string command, vector<string> &result) {

	//split input string at spaces
	vector<string> splitCommand;
	char space = ' ';
	split(command, space, splitCommand);
	//cerr << splitCommand.size() << endl;

	//rejoin substrings surrounded by quotation marks
	char quotmark = '"';
	vector<string>::iterator iter;
	if(splitCommand.size() > 1) {
		for(iter = splitCommand.begin(); (iter != splitCommand.end()); iter++) {
			size_t posStart = iter->find(quotmark);
			size_t posEnd = iter->rfind(quotmark);
			if(posStart == string::npos) {
				continue;
			} else if ((posStart != 0) || ((posEnd > 0) && (posEnd < ((iter->length())-1)))) {
				cerr << "ErrorCommandFormat" << endl;
				return error;
			} else if((posStart == 0) && (iter->length() == 1)) {
				cerr << "ErrorCommandFormat" << endl;
				return error;
			}
			vector<string>::iterator curr = iter+1;
			bool startQuot = true;
			while((posStart == 0) && (posEnd != iter->length()-1)) {
				if(curr == splitCommand.end()) {
					cerr << "ErrorCommandFormat" << endl;
					return error;
				}
				//remove starting quotation once
				if(startQuot) {
					*iter = iter->substr(1,iter->length()-1);
					startQuot = false;
				}
				iter->append(" ");
				iter->append(*curr);
				curr = splitCommand.erase(curr);
				posEnd = iter->rfind(quotmark);
				if((posEnd > 0) && (posEnd < ((iter->length())-1))) {
					cerr << "ErrorCommandFormat" << endl;
					return error;
				}
			}
			//remove final quotation if starting quotation was removed.
			if(!startQuot) *iter = iter->substr(0,iter->length()-1);
		}
	}
	result.swap(splitCommand);
	string commWord = *result.begin();
	for(int i = 0; commWord[i]; i++) commWord[i] = tolower(commWord[i]);
	//cerr << commWord << endl;
	return getCommandID(commWord);
}

/* 
 * 
 */
Commands CommandParser::getCommandID(string command) {
	KeywordMap* keywords = new KeywordMap();
	return keywords->lookup(command);
}

/*
 * Splits the inputString at positions of splitChar and appends the substrings to output.
 * Resizes output.
 */
void CommandParser::split(string inputString, char splitChar, vector<string> & output) {
	size_t pos = inputString.find(splitChar);
	//output.resize(output.size()+1);
	if(pos == string::npos) {
		//splitChar not found? input is output!
		//output.back() = inputString;
		output.push_back(inputString);
	} else {
		//splitChar found? Append first substring and
		//output.back() = inputString.substr(0,pos-1);
		output.push_back(inputString.substr(0,pos));
		//use split on second substring.
		split(inputString.substr(pos+1,inputString.length()-1), splitChar, output);
	}
}

/*
 * Checks if the string passed as stPSM matches any PageSegMode. If it does, the PageSegMode is stored to target and true is returned.
 * If it doesn't, returns false.
 */
bool CommandParser::getPageSegMode(string stPSM, PageSegMode* target){
	//all chars to upper case
	for (int i = 0; i < (int) stPSM.length(); i++) {
		if(stPSM[i] != '_') stPSM[i]=toupper(stPSM[i]);
	}
	//search for fit
	map<string, PageSegMode>::iterator result = psmStrings.find(stPSM);
	//didn't find any?
	if(result == psmStrings.end()) {
		cerr << "ErrorParseFailed" << endl;
		return false;
	}
	//return result
	*target = psmStrings.find(stPSM)->second;
	return true;
}

/*
 * Tries to match the PageSegMode to an equivalent string. On success saves the string at target and returns true.
 * Returns false if match fails.
 */
bool CommandParser::getPSMString(PageSegMode psm, string* target){
	for(map<string, PageSegMode>::iterator iter = psmStrings.begin(); iter != psmStrings.end(); iter++) {
		if(iter->second == psm) {
			*target = iter->first;
			return true;
		}
	}
	return false;
}

/*
 * Checks if the string passed as stOEM matches any OcrEngineMode. If it does, the OcrEngineMode is stored to target and true is returned.
 * If it doesn't, returns false.
 */
bool CommandParser::getOcrEngineMode(string stOEM, OcrEngineMode* target){
	//all chars to upper case
	for (int i = 0; i < (int) stOEM.length(); i++) {
		if(stOEM[i] != '_') stOEM[i]=toupper(stOEM[i]);
	}
	//search for fit
	map<string, OcrEngineMode>::iterator result = oemStrings.find(stOEM);
	//didn't find any?
	if(result == oemStrings.end()) {
		cerr << "ErrorParseFailed" << endl;
		return false;
	}
	//return result
	*target = oemStrings.find(stOEM)->second;
	return true;
}

/*
 * Tries to match the OcrEngineMode to an equivalent string. On success saves the string at target and returns true.
 * Returns false if match fails.
 */
bool CommandParser::getOEMString(OcrEngineMode oem, string* target){
	for(map<string, OcrEngineMode>::iterator iter = oemStrings.begin(); iter != oemStrings.end(); iter++) {
		if(iter->second == oem) {
			*target = iter->first;
			return true;
		}
	}
	return false;
}

