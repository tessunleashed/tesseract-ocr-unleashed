/*
 * KeywordMap.cpp
 * 
 */

#include "stdafx.h"
#include "KeywordMap.h"
#include <iostream>


KeywordMap::KeywordMap() {
	setKeywords();

}

KeywordMap::~KeywordMap() {
	Keywords.clear();
}
/*
 *
 */
void KeywordMap::setKeywords() {
	Keywords["quit"] = quit;
	Keywords["exit"] = quit;
	Keywords["stop"] = quit;
	Keywords["shutdown"] = quit;
	Keywords["end"] = end;
	Keywords["init"] = init;
	Keywords["path"] = path;
	Keywords["lang"] = lang;
	Keywords["test"] = test;
	Keywords["version"] = version;
	Keywords["clear"] = clear;
	Keywords["setvariable"] = setvariable;
	Keywords["setdebugvariable"] = setdebugvariable;
	Keywords["setinputname"] = setinputname;
	Keywords["setoutputname"] = setoutputname;
	Keywords["getintvariable"] = getintvariable;
	Keywords["getboolvariable"] = getboolvariable;
	Keywords["getdoublevariable"] = getdoublevariable;
	Keywords["getstringvariable"] = getstringvariable;
	Keywords["printvariables"] = printvariables;
	Keywords["getvariableasstring"] = getvariableasstring;
	Keywords["getinitlanguagesasstring"] = getinitlanguagesasstring;
	Keywords["getloadedlanguagesasvector"] = getloadedlanguagesasvector;
	Keywords["getavailablelanguagesasvector"] = getavailablelanguagesasvector;
	Keywords["initlangmod"] = initlangmod;
	Keywords["initforanalysepage"] = initforanalysepage;
	Keywords["readconfigfile"] = readconfigfile;
	Keywords["readdebugconfigfile"] = readdebugconfigfile;
	Keywords["setpagesegmode"] = setpagesegmode;
	Keywords["getpagesegmode"] = getpagesegmode;
	Keywords["tesseractrect"] = tesseractrect;
	Keywords["clearadaptiveclassifier"] = clearadaptiveclassifier;
	Keywords["setimage"] = setimage;
	Keywords["setsourceresolution"] = setsourceresolution;
	Keywords["setrectangle"] = setrectangle;
	Keywords["getthresholdedimagescalefactor"] = getthresholdedimagescalefactor;
	Keywords["recognize"] = recognize;
	Keywords["recognizeforchoptest"] = recognizeforchoptest;
	Keywords["processpages"] = processpages;
	Keywords["getutf8text"] = getutf8text;
	Keywords["gethocrtext"] = gethocrtext;
	Keywords["getboxtext"] = getboxtext;
	Keywords["getunlvtext"] = getunlvtext;
	Keywords["meantextconf"] = meantextconf;
	Keywords["allwordconfidences"] = allwordconfidences;
	Keywords["adapttowordstr"] = adapttowordstr;
	Keywords["isvalidword"] = isvalidword;
	Keywords["gettextdirection"] = gettextdirection;
	Keywords["getunichar"] = getunichar;
	Keywords["numdawgs"] = numdawgs;
	Keywords["maketessocrrow"] = maketessocrrow;
	Keywords["getoemstring"] = getoemstring;
	Keywords["set_min_orientation_margin"] = set_min_orientation_margin;
	Keywords["findlinescreateblocklist"] = findlinescreateblocklist;
	Keywords["deleteblocklist"] = deleteblocklist;
	Keywords["gethtmltext"] = gethtmltext;
	Keywords["help"] = help;
}

/*
 *
 */
Commands KeywordMap::lookup(string key) {
	map<string, Commands>::iterator result = Keywords.find(key);
	if(result == Keywords.end()) {
		cerr << "ErrorParseFailed: " << key << endl;
		return error;
	}
	return Keywords.find(key)->second;
}
