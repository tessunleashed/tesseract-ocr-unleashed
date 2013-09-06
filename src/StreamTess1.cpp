//============================================================================
// Name        : StreamTess1.cpp
// Author      : Max Peters
// Version     : 0.0.0.1
// Copyright   : Copyright 2013 Max Peters
// Description : Tesseract Stream IO
//============================================================================

#include <iostream>
#include <string>
#include "baseapi.h"
#include "allheaders.h"
#include "CommandParser.h"
#include "KeywordMap.h"
#include "InputHandler.h"
#include "stdafx.h"

using namespace std;
using namespace tesseract;

int main(int argc, char *argv[]) {
	InputHandler* ihandle = new InputHandler();
	ihandle->start(argc, argv);
	delete ihandle;
//	bool doExit = false;
//	int commandSize = 512;
//	char commandDelimiter = '\n';
//	char commandChar[commandSize];
//	CommandParser* parser = new CommandParser();
//	while (!doExit) {
//		cout << "Ready! Please submit command!\n";
//		cin.getline(commandChar, commandSize, commandDelimiter);
//		string command = (string) commandChar;
//		//remove newline characters
//		if(commandDelimiter != '\n') {
//			size_t newLinePos = command.find('\n');
//			if (newLinePos == 0) {
//				command = command.replace(newLinePos,1,"");
//			}
//		}
//		//remove delimiter
//		size_t delimPos = command.find(commandDelimiter);
//		if (delimPos != string::npos) {
//			if(delimPos != (command.length()-1)) {
//				cerr << "Warning: Delimiter " << commandDelimiter << " not at end of line. ";
//				cerr << "Everything behind the delimiter is ignored.\n";
//			}
//			command = command.substr(0,delimPos);
//		}
//		//cout << "Parsing...!\n";
//		//parse command into parameter vector
//		vector<string> parsedCommand;
//		Commands commID = parser->parse(command, parsedCommand);
//		if(commID == error) {
//			doExit = true;
//		} else if(commID == init) {
//			if(parsedCommand.size() == 3) {
//
//			} else {
//
//			}
//		} else if(commID == path) {
//
//		} else if(commID == lang) {
//
//		} else if(commID == init) {
//
//		} else if(commID == init) {
//
//		}
//		if (commID != error) {
//			switch(commID) {
//			case init: break;
//			case path: break;
//			case lang: break;
//			case image: break;
//			case quit: doExit = true; break;
//			default: break;
//			}
//			//cout << commID;
//			//cout << "\n";
//			//cout << "Parsed!\n";
//			//vector<string>::iterator iter;
//			//for(iter = parsedCommand.begin(); iter != parsedCommand.end(); iter++) {
//			//	cout << *iter;
//			//	cout << "\n";
//			//}
//			//if(parsedCommand.begin()->compare("quit") == 0) doExit = true;
//			//cout << parsedCommand.size();
//			//cout << "\n";
//		} else {
//			cerr << "Invalid Command: Could not process.\n";
//		}
//	}
//
//	const char* path = "/home/max/Dropbox/BA/workspace/StreamTess1/Debug/tessdata";
//	const char* lang = "eng+deu";
//	string initPath;
//	string initLang;
//
//	string imagePath;
//	const char* image = "/home/max/Dropbox/BA/workspace/StreamTess1/Debug/deu1.png";
//
//	//TODO: Extract all functionality into seperate methods
//
//	//create TessBaseAPI object
//	TessBaseAPI *myTess = new TessBaseAPI();
//
//	//TODO: Wait for language selection input
//	printf("Please specify tessdata path (enter x for default).\n");
//	cin >> initPath;
//	if(!(initPath=="x")) path = initPath.c_str();
//	printf("Please specify languages (enter x for default).\n");
//	cin >> initLang;
//	if(!(initLang=="x")) lang = initLang.c_str();
//
//	//initialize myTess
//	printf("Initializing tesseract...\n");
//	myTess->Init(path,lang);
//	printf("Done!\n");
//
//	//TODO: Wait for Image input
//	printf("Please specify image path and name (enter x for default).\n");
//	cin >> imagePath;
//	if(!(imagePath=="x")) image = imagePath.c_str();
//
//	//TODO: Transform image data to PIX.
//
//	//TODO: Feed image to tesseract
//	FILE* fin = fopen(image, "rb");
//	if (fin == NULL) {
//		printf("Cannot open input file: %s\n", image);
//		exit(2);
//	}
//	fclose(fin);
//
//	PIX   *pixs;
//	if ((pixs = pixRead(image)) == NULL) {
//		printf("Unsupported image type.\n");
//		exit(3);
//	}
//	pixDestroy(&pixs);
//
//	STRING text_out;
//	if (!myTess->ProcessPages(image, NULL, 0, &text_out)) {
//		printf("Error during processing.\n");
//	}
//
//	//TODO: Write output back to where the input came from
//	cout << text_out.string();
//
//	//TODO: Wait for kill signal
//	printf("Type anything and press enter to quit.\n");
//	string blob;
//	cin >> blob;
//	//finalize myTess
//	myTess->End();
//
//	printf("Tesseract quit.\n");

	return 0;
}
