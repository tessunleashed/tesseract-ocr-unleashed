/*
 * KeywordMap.h
 */

#ifndef KEYWORDMAP_H_
#define KEYWORDMAP_H_

#include <map>
#include <string>

using namespace std;

enum Commands { error=-1,
				quit=0,
				end=1,
				init=2,
				path=3,
				lang=4,
				test=5,
				version=6,
				clear=7,
				setvariable=8,
				setdebugvariable=9,
				setinputname=10,
				setoutputname=11,
				getintvariable=12,
				getboolvariable=13,
				getdoublevariable=14,
				getstringvariable=15,
				printvariables=16,
				getvariableasstring=17,
				getinitlanguagesasstring=18,
				getloadedlanguagesasvector=19,
				getavailablelanguagesasvector=20,
				initlangmod=21,
				initforanalysepage=22,
				readconfigfile=23,
				readdebugconfigfile=24,
				setpagesegmode=25,
				getpagesegmode=26,
				tesseractrect=27,
				clearadaptiveclassifier=28,
				setimage=29,
				setsourceresolution=30,
				setrectangle=31,
				getthresholdedimagescalefactor=32,
				recognize=33,
				recognizeforchoptest=34,
				processpages=35,
				getutf8text=36,
				gethocrtext=37,
				getboxtext=38,
				getunlvtext=39,
				meantextconf=40,
				allwordconfidences=41,
				adapttowordstr=42,
				isvalidword=43,
				gettextdirection=44,
				getunichar=45,
				numdawgs=46,
				maketessocrrow=47,
				getoemstring=48,
				set_min_orientation_margin=49,
				findlinescreateblocklist=50,
				deleteblocklist=51,
				gethtmltext=52,
				help=53,
				};

class KeywordMap {
public:
	KeywordMap();
	virtual ~KeywordMap();
	Commands lookup(string key);
private:
	void setKeywords();
	map<string, Commands> Keywords;
};
#endif /* KEYWORDMAP_H_ */
