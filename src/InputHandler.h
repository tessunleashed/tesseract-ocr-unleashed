/*
 * InputHandler.h
 *
 *  Created on: 26.06.2013
 *      Author: max
 */

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <string>
#include "baseapi.h"
#include "allheaders.h"
#include "CommandParser.h"
using namespace tesseract;

class InputHandler {
public:
	InputHandler();
	virtual ~InputHandler();
	void start(int argc, char *argv[]);
private:
	//member variables
	TessBaseAPI* myTess;
	bool doExit;
	bool isInit;
	bool silent;
	vector<string> parsedCommand;
	int commandSize;
	char commandDelimiter;
	char* commandChar;
	CommandParser* parser;
	string stPath;
	string stLang;
	BLOCK_LIST* currentBlocks;
	//own calls
	void commPath();
	void commLang();
	void commTest();
	void commGetHTMLText();
	void commHelp();
	//tesseract call procedures
	void tessEnd();
	bool tessInit();
	void tessSetImage();
	bool tessSetVariable(bool debug);
	void tessTesseractRect();
	void tessVersion();
	void tessClear();
	void tessSetInputName();
	void tessSetOutputName();
	void tessGetIntVariable();
	void tessGetBoolVariable();
	void tessGetDoubleVariable();
	void tessGetStringVariable();
	void tessPrintVariables();
	void tessGetVariableAsString();
	void tessGetInitLanguagesAsString();
	void tessGetLoadedLanguagesAsString();
	void tessGetAvailableLanguagesAsVector();
	void tessInitLangMod();
	void tessInitForAnalysePage();
	void tessReadConfigFile();
	void tessReadDebugConfigFile();
	void tessSetPageSegMode();
	void tessGetPageSegMode();
	void tessClearAdaptiveClassifier();
	void tessSetSourceResolution();
	void tessSetRectangle();
	void tessGetThresholdedImageScaleFactor();
	void tessRecognize();
	void tessRecognizeForChopTest();
	void tessProcessPages();
	void tessGetUTF8Text();
	void tessGetHOCRText();
	void tessGetBoxText();
	void tessGetUNLVText();
	void tessMeanTextConf();
	void tessAllWordConfidences();
	void tessAdaptToWordStr();
	void tessIsValidWord();
	void tessGetTextDirection();
	void tessGetUniChar();
	void tessNumDawgs();
	void tessMakeTessOCRRow();
	void tessGetOEMString();
	void tessSetMinOrientationMargin();
	void tessFindLinesCreateBlockList();
	void tessDeleteBlockList();
	//helper functions
	bool checkNumberOfArguments(int expectedArguments);
	bool checkInit();
	PIX* readImageToPix();
	void readImageData(const l_uint8 *data);
	void sendWrongNumberOfArgumentsError();
};

#endif /* INPUTHANDLER_H_ */
