/*
 * InputHandler.cpp
 */
#include "stdafx.h"
#include "InputHandler.h"
#include "CommandParser.h"
#include "KeywordMap.h"
#include <iostream>
#include <fstream>
#include <baseapi.h>
#include "allheaders.h"
//#include "base64.h"

//#ifdef _WIN32
//#include <fcntl.h>
//#include <io.h>
//#endif  // _WIN32


using namespace std;

InputHandler::InputHandler() {
    isInit = false;
    doExit = false;
    silent = false;
    commandSize = 512;
    commandDelimiter = '\n';
    commandChar = new char[commandSize];
    parser = new CommandParser();
    myTess = new TessBaseAPI();
    stPath = "../tessdata";
    stLang = "eng";
}

InputHandler::~InputHandler() {
    delete[] commandChar;
    parser->~CommandParser();
    myTess->~TessBaseAPI();
}

void InputHandler::start(int argc, char *argv[]) {

    //#ifdef WIN32
    //    if (_setmode(_fileno(stdin), _O_BINARY) == -1) cerr << "ERROR: cin to binary" << endl;
    //#endif  // WIN32

    //    for (int i = 0; i < argc; i++) {
    //        cout << argv[i];
    //    }
    while (!doExit) {
        string silentMode = "-silent";
        //try to initialize if parameters were passed on start
        //if(argc == 3) {
        //    stPath = argv[1];
        //    stLang = argv[2];
        //    int initRes = myTess->Init(stPath.c_str(), stLang.c_str());
        //    if(initRes != 0) {
        //        cerr << "ErrorStartInitFailed" << endl;
        //    } else {
        //        isInit = true;
        //    }
        //}
        if(argc == 2) {
            if(silentMode.compare(argv[1]) == 0) {
                silent = true;
            }
        }
        if(!silent) cout << "SubmitCommand" << endl;
        cin.getline(commandChar, commandSize, commandDelimiter);
        //cin.clear();
        string command = (string) commandChar;
        //remove \r
        if((0 < command.find('\r')) && (command.find('\r') < command.size())) {
            command.erase(command.find('\r'),1);
        }
        //remove newline characters
        if(commandDelimiter != '\n') {
            size_t newLinePos = command.find('\n');
            if (newLinePos == 0) {
                command = command.replace(newLinePos,1,"");
            }
        }
        //remove delimiter
        size_t delimPos = command.find(commandDelimiter);
        if (delimPos != string::npos) {
            //if(delimPos != (command.length()-1)) {
            //    cerr << "Warning: Delimiter " << commandDelimiter << " not at end of line. ";
            //    cerr << "Everything behind the delimiter is ignored.\n";
            //}
            command = command.substr(0,delimPos);
        }
        //parse command into parameter vector
        //vector<string> parsedCommand;
        Commands commID = parser->parse(command, parsedCommand);
        //analyse commID and act accordingly
        //Error
        if(commID == error) {
            //doExit = true;
        } else if(commID == quit) {
            doExit = true;
            //End
        } else if(commID == end) {
            tessEnd();
            //Init
        } else if(commID == init) {
            tessInit();
            //Path
        } else if(commID == path) {
            commPath();
            //Lang
        } else if(commID == lang) {
            commLang();
            //Test
        } else if(commID == test) {
            commTest();
            //SetImage
        } else if(commID == setimage) {
            tessSetImage();
            //Version
        } else if(commID == version) {
            tessVersion();
            //Clear
        } else if(commID == clear) {
            tessClear();
            //SetVariable
        } else if(commID == setvariable) {
            tessSetVariable(false);
            //SetDebugVariable
        } else if(commID == setdebugvariable) {
            tessSetVariable(true);
            //SetInputName
        } else if(commID == setinputname) {
            tessSetInputName();
            //SetOutputName
        } else if(commID == setoutputname) {
            tessSetOutputName();
            //GetIntVariable
        } else if(commID == getintvariable) {
            tessGetIntVariable();
            //GetBoolVariable
        } else if(commID == getboolvariable) {
            tessGetBoolVariable();
            //GetDoubleVariable
        } else if(commID == getdoublevariable) {
            tessGetDoubleVariable();
            //GetStringVariable
        } else if(commID == getstringvariable) {
            tessGetStringVariable();
            //PrintVariables
        } else if(commID == printvariables) {
            tessPrintVariables();
            //GetVariableAsString
        } else if(commID == getvariableasstring) {
            tessGetVariableAsString();
            //GetInitLanguagesAsString
        } else if(commID == getinitlanguagesasstring) {
            tessGetInitLanguagesAsString();
            //GetLoadedLanguagesAsString
        } else if(commID == getloadedlanguagesasvector) {
            tessGetLoadedLanguagesAsString();
            //GetAvailableLanguagesAsString
        } else if(commID == getavailablelanguagesasvector) {
            tessGetAvailableLanguagesAsVector();
            //InitLangMod
        } else if(commID == initlangmod) {
            tessInitLangMod();
            //InitForAnalysePage
        } else if(commID == initforanalysepage) {
            tessInitForAnalysePage();
            //ReadConfigFile
        } else if(commID == readconfigfile) {
            tessReadConfigFile();
            //ReadDebugConfigFile
        } else if(commID == readdebugconfigfile) {
            tessReadDebugConfigFile();
            //SetPageSegMode
        } else if(commID == setpagesegmode) {
            tessSetPageSegMode();
            //GetPageSegMode
        } else if(commID == getpagesegmode) {
            tessGetPageSegMode();
            //TesseractRect
        } else if(commID == tesseractrect) {
            tessTesseractRect();
            //ClearAdaptiveClassifier
        } else if(commID == clearadaptiveclassifier) {
            tessClearAdaptiveClassifier();
            //SetSourceResolution
        } else if(commID == setsourceresolution) {
            tessSetSourceResolution();
            //SetRectangle
        } else if(commID == setrectangle) {
            tessSetRectangle();
            //GetThresholdedImageScaleFactor
        } else if(commID == getthresholdedimagescalefactor) {
            tessGetThresholdedImageScaleFactor();
            //Recognize
        } else if(commID == recognize) {
            tessRecognize();
            //RecognizeForChopTest
        } else if(commID == recognizeforchoptest) {
            tessRecognizeForChopTest();
            //ProcessPages
        } else if(commID == processpages) {
            tessProcessPages();
            //GetUTF8Text
        } else if(commID == getutf8text) {
            tessGetUTF8Text();
            //GetHOCRText
        } else if(commID == gethocrtext) {
            tessGetHOCRText();
            //GetBoxText
        } else if(commID == getboxtext) {
            tessGetBoxText();
            //GetUNLVText
        } else if(commID == getunlvtext) {
            tessGetUNLVText();
            //MeanTextConf
        } else if(commID == meantextconf) {
            tessMeanTextConf();
            //AllWordConfidences
        } else if(commID == allwordconfidences) {
            tessAllWordConfidences();
            //AdaptToWordStr
        } else if(commID == adapttowordstr) {
            tessAdaptToWordStr();
            //IsValidWord
        } else if(commID == isvalidword) {
            tessIsValidWord();
            //GetTextDirection
        } else if(commID == gettextdirection) {
            tessGetTextDirection();
            //GetUnichar
        } else if(commID == getunichar) {
            tessGetUniChar();
            //NumDawgs
        } else if(commID == numdawgs) {
            tessNumDawgs();
            //MakeTessOCRRow
        } else if(commID == maketessocrrow) {
            tessMakeTessOCRRow();
            //oem
        } else if(commID == getoemstring) {
            tessGetOEMString();
            //set_min_orientation_margin
        } else if(commID == set_min_orientation_margin) {
            tessSetMinOrientationMargin();
            //FindLinesCreateBlockList
        } else if(commID == findlinescreateblocklist) {
            tessFindLinesCreateBlockList();
            //DeleteBlockList
        } else if(commID == deleteblocklist) {
            tessDeleteBlockList();
            //GetHTMLText
        } else if(commID == gethtmltext) {
            commGetHTMLText();
            //Help
        } else if(commID == help) {
            commHelp();
        }
        //cin.clear();
    }
    tessEnd();
}

//path procedure
void InputHandler::commPath() {
    if(checkNumberOfArguments(1)) {
        stPath = parsedCommand[1];
    } else {
        sendWrongNumberOfArgumentsError();
    }
}
//lang procedure
void InputHandler::commLang() {
    if(checkNumberOfArguments(1)) {
        stLang = parsedCommand[1];
    } else {
        sendWrongNumberOfArgumentsError();
    }
}
//test procedure
void InputHandler::commTest() {
    /*if(checkInit()) {
        FILE* fp = fopen("help.txt", "r");
        myTess->PrintVariables(fp);
        fclose(fp);
    }*/
    /*
    if (isInit && checkNumberOfArguments(0)) {
        for(int i = 0; i < 50; i++) {
            FILE *file;
            file = fopen("/home/max/Arbeitsfläche/eng1.png", "rb");
            fseek (file , 0 , SEEK_END);
            size_t length=ftell (file);
            rewind (file);
            char* dstTmp = (char*) malloc (sizeof(char)*length);
            fread (dstTmp,1,length,file);
            fclose(file);
            cerr << length << endl;
            //                double i = 0;
            //                while ((length - i) > 1) {
            //                    cerr << dstTmp[(int) i];
            //                    i++;
            //                } cerr << endl;
            l_uint8* data = (l_uint8*) malloc (sizeof(l_uint8)*length);
            memcpy(data, dstTmp, length);
            string code = base64_encode(data, length);
            cerr << code.length() << endl;
            cerr << code << endl;
            string x = base64_decode(code);
            size_t size = x.length();
            //                cerr << x << endl;
            l_uint8* xdata = (l_uint8*) malloc (sizeof(l_uint8)*size);
            memcpy(xdata, x.data(), size);
            PIX* pixd = pixReadMem(xdata,size);
            myTess->SetImage(pixd);
            cerr << myTess->GetUTF8Text();
            pixDestroy(&pixd);
            delete[] data;
            delete[] xdata;
            delete[] dstTmp;
        }
    }
    */
}

//GetHTMLText
void InputHandler::commGetHTMLText() {
    if(checkInit()) {
        if(checkNumberOfArguments(1)) {
            int pageNumber = 0;
            pageNumber = atoi(parsedCommand[1].c_str());
            char* result = myTess->GetHOCRText(pageNumber);
            cout << "<html>" << endl << "<body>" << endl;
            cout << result << endl;
            cout << "</body>" << endl << "</html>" << endl;
        delete[] result;
        } else {
            sendWrongNumberOfArgumentsError();
        }
    }
}

//Help
void InputHandler::commHelp() {
    string line;
    ifstream myfile ("./help.txt");
    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            getline (myfile,line);
            cout << line << endl;
        }
        myfile.close();
    } else {
        cout << "ErrorCouldNotFindHelpFile" << endl;
    }
}


/*
 * Tesseract call procedures
 */
void InputHandler::tessEnd() {
    if(checkNumberOfArguments(0)) {
        if(isInit) {
            myTess->End();
            isInit = false;
        }
    } else {
        sendWrongNumberOfArgumentsError();
    }
}

bool InputHandler::tessInit() {
    if(isInit) {
        cerr << "ErrorTesseractAlreadyInitialized" << endl;
        return false;
    } else {
        int initRes = -1;
        if(checkNumberOfArguments(2)) {
            stPath = parsedCommand[1].c_str();
            stLang = parsedCommand[2].c_str();
            initRes = myTess->Init(stPath.c_str(), stLang.c_str());
        } else if(checkNumberOfArguments(3)){
            stPath = parsedCommand[1].c_str();
            stLang = parsedCommand[2].c_str();
            tesseract::OcrEngineMode* oem = new tesseract::OcrEngineMode();
            *oem = OEM_DEFAULT;
            parser->getOcrEngineMode(parsedCommand[3], oem);
            initRes = myTess->Init(stPath.c_str(), stLang.c_str(), *oem);
        } else if(checkNumberOfArguments(0)){
            initRes = myTess->Init(stPath.c_str(), stLang.c_str());
        } else {
            sendWrongNumberOfArgumentsError();
            return false;
        }
        if(initRes != 0) {
            cerr << "ErrorTesseractNotInitialized" << endl;
            return false;
        }
        isInit = true;
        return true;
    }
}

void InputHandler::tessSetImage() {
    if(checkInit()) {
        myTess->Clear();
        if(checkNumberOfArguments(1)) {
            //        cerr << "receiving image" << endl;
            PIX* imagePix;
            try {
                imagePix = readImageToPix();
            } catch (...) {
                cerr << "ExceptionOnImageProcessing" << endl;
            }
            if(imagePix != NULL) {
                //        cerr << "sending image" << endl;
                myTess->SetImage(imagePix);
                //        cerr << "image sent" << endl;
                pixDestroy(&imagePix);
            }
        } else if(checkNumberOfArguments(5)) {
            //ask for image data
            const l_uint8* dataConst;
            readImageData(dataConst);
            int width = atoi(parsedCommand[2].c_str());
            int height = atoi(parsedCommand[3].c_str());
            int bytesPerPixel = atoi(parsedCommand[4].c_str());
            int bytesPerLine = atoi(parsedCommand[5].c_str());
            myTess->SetImage(dataConst, width, height, bytesPerPixel, bytesPerLine);
        } else {
            sendWrongNumberOfArgumentsError();
        }
    }
}
//setDebugVariable and setVeriable implementation
bool InputHandler::tessSetVariable(bool debug) {
    if (checkInit()) {
        if(checkNumberOfArguments(2)) {
            string name = parsedCommand[1];
            string value = parsedCommand[2];
            bool result;
            if(debug) {
                result = myTess->SetDebugVariable(name.c_str(), value.c_str());
            } else {
                result = myTess->SetVariable(name.c_str(), value.c_str());
            }
            if (!result) {
                cerr << "ErrorTesseractCallFailed" << endl;
                return false;
            }
            return true;
        } else {
            sendWrongNumberOfArgumentsError();
            return false;
        }
    } else {
        return false;
    }
}

void InputHandler::tessTesseractRect() {
    if(checkInit()) {
        if(checkNumberOfArguments(7)) {
            //clear old data
            myTess->Clear();
            //cast parsed command
            int bytes_per_pixel = atoi(parsedCommand[2].c_str());
            int bytes_per_line = atoi(parsedCommand[3].c_str());
            int left = atoi(parsedCommand[4].c_str());
            int top = atoi(parsedCommand[5].c_str());
            int width = atoi(parsedCommand[6].c_str());
            int height = atoi(parsedCommand[7].c_str());
            //ask for image data
            const l_uint8* dataConst;
            readImageData(dataConst);
            //try {
                char* result = myTess->TesseractRect(dataConst, bytes_per_pixel, bytes_per_line, left, top, width, height);
                cout << result << endl;
            //} catch (exception& e) {
            //    cerr << "ErrorException" << endl;
            //}
        } else {
            sendWrongNumberOfArgumentsError();
        }
    }
}

void InputHandler::tessVersion() {
    cout << myTess->Version() << "\n";
}

void InputHandler::tessClear() {
    if(checkInit()) {
        myTess->Clear();
    }
}

void InputHandler::tessSetInputName() {
    if(checkNumberOfArguments(1)) {
        string name = parsedCommand[1];
        myTess->SetInputName(name.c_str());
    } else {
        sendWrongNumberOfArgumentsError();
    }
}

void InputHandler::tessSetOutputName() {
    if(checkNumberOfArguments(1)) {
        string name = parsedCommand[1];
        myTess->SetOutputName(name.c_str());
    } else {
        sendWrongNumberOfArgumentsError();
    }
}

void InputHandler::tessGetIntVariable() {
    if(checkInit()) {
        if(checkNumberOfArguments(1)) {
            string name = parsedCommand[1];
            int value;
            int* valpoint = &value;
            bool result = myTess->GetIntVariable(name.c_str(), valpoint);
            if(!result) {
                cerr << "ErrorTesseractCallFailed" << endl;
            } else {
                cout << value << endl;
            }
        } else {
            sendWrongNumberOfArgumentsError();
        }
    }
}

void InputHandler::tessGetBoolVariable() {
    if(checkInit()) {
        if(checkNumberOfArguments(1)) {
            string name = parsedCommand[1];
            bool value;
            bool* valpoint = &value;
            bool result = myTess->GetBoolVariable(name.c_str(), valpoint);
            if(!result) {
                cerr << "ErrorTesseractCallFailed" << endl;
            } else {
                cout << value << "\n";
            }
        } else {
            sendWrongNumberOfArgumentsError();
        }
    }
}

void InputHandler::tessGetDoubleVariable() {
    if(checkInit()) {
        if(checkNumberOfArguments(1)) {
            string name = parsedCommand[1];
            double value;
            double* valpoint = &value;
            bool result = myTess->GetDoubleVariable(name.c_str(), valpoint);
            if(!result) {
                cerr << "ErrorTesseractCallFailed" << endl;
            } else {
                cout << value << "\n";
            }
        } else {
            sendWrongNumberOfArgumentsError();
        }
    }
}

void InputHandler::tessGetStringVariable() {
    if(checkInit()) {
        if(checkNumberOfArguments(1)) {
            string name = parsedCommand[1];
            string value = myTess->GetStringVariable(name.c_str());
            cout << value << "\n";
        } else {
            sendWrongNumberOfArgumentsError();
        }
    }
}

void InputHandler::tessPrintVariables() {
    if(checkInit()) {
        if(checkNumberOfArguments(1)) {
            string filename = parsedCommand[1];
            FILE* fp = fopen(filename.c_str(), "ab+");
            myTess->PrintVariables(fp);
            fclose(fp);
        } else {
            sendWrongNumberOfArgumentsError();
        }
    }
}
void InputHandler::tessGetVariableAsString() {
    if(checkInit()) {
        if(checkNumberOfArguments(1)) {
            string name = parsedCommand[1];
            STRING value;
            STRING* valPointer = &value;
            bool result = myTess->GetVariableAsString(name.c_str(), valPointer);
            if(result) {
                cout << value.string() << endl;
            } else {
                cerr << "ErrorTesseractCallFailed" << endl;
            }
        } else {
            sendWrongNumberOfArgumentsError();
        }
    }
}

void InputHandler::tessGetInitLanguagesAsString() {
    if(checkInit()) {
        string initLangs = myTess->GetInitLanguagesAsString();
        cout << initLangs << "\n";
    }
}

void InputHandler::tessGetLoadedLanguagesAsString() {
    if(checkInit()) {
        GenericVector<STRING> *loadedLangs = new GenericVector<STRING>(0);
        myTess->GetLoadedLanguagesAsVector(loadedLangs);
        int length = loadedLangs->length();
        if(length == 0) {
            cerr << "ErrorTesseractCallFailed" << endl;
        } else {
            for (int i = 0; i < length; i++) {
                STRING s = loadedLangs->get(i);
                cout << s.string() << endl;
            }
        }
        loadedLangs->~GenericVector();
        delete loadedLangs;
    }
}

void InputHandler::tessGetAvailableLanguagesAsVector() {
    if (checkInit()) {
        GenericVector<STRING> *availableLangs = new GenericVector<STRING>(0);
        myTess->GetAvailableLanguagesAsVector(availableLangs);
        int length = availableLangs->length();
        if(length == 0) {
            cerr << "ErrorTesseractCallFailed" << endl;
        } else {
            for (int i = 0; i < length; i++) {
                STRING s = availableLangs->get(i);
                cout << s.string() << endl;
            }
        }
        availableLangs->~GenericVector();
        delete availableLangs;
    }
}

void InputHandler::tessInitLangMod() {
    if (checkNumberOfArguments(2)) {
        stPath = parsedCommand[1];
        stLang = parsedCommand[2];
    } else {
        sendWrongNumberOfArgumentsError();
    }
    int result = myTess->InitLangMod(stPath.c_str(),stLang.c_str());
    if(result != 0) {
        cerr << "ErrorTesseractCallFailed" << endl;
    }
}

void InputHandler::tessInitForAnalysePage() {
        myTess->InitForAnalysePage();
}

void InputHandler::tessReadConfigFile() {
    if(checkInit()) {
        if(checkNumberOfArguments(1)) {
            myTess->ReadConfigFile(parsedCommand[1].c_str());
        } else {
            sendWrongNumberOfArgumentsError();
        }
    }
}

void InputHandler::tessReadDebugConfigFile() {
    if(checkInit()) {
        if(checkNumberOfArguments(1)) {
            myTess->ReadDebugConfigFile(parsedCommand[1].c_str());
        } else {
            sendWrongNumberOfArgumentsError();
        }
    }
}

void InputHandler::tessSetPageSegMode() {
    if(checkInit()) {
        if(checkNumberOfArguments(1)) {
            tesseract::PageSegMode* target = new tesseract::PageSegMode();
            *target = PSM_AUTO;
            bool result = parser->getPageSegMode(parsedCommand[1], target);
            if(result) {
                myTess->SetPageSegMode(*target);
            }
        } else {
            sendWrongNumberOfArgumentsError();
        }
    }
}

void InputHandler::tessGetPageSegMode() {
    if(checkInit()) {
        tesseract::PageSegMode psm = myTess->GetPageSegMode();
        string tarString = "";
        string* target = &tarString;
        bool result = parser->getPSMString(psm, target);
        if(result) {
            cout << tarString << "\n";
        }
    }
}

void InputHandler::tessClearAdaptiveClassifier() {
    if(checkInit()) {
        myTess->ClearAdaptiveClassifier();
    }
}

void InputHandler::tessSetSourceResolution() {
    if(checkInit()) {
        if(checkNumberOfArguments(1)) {
            int ppi = atoi(parsedCommand[1].c_str());
            myTess->SetSourceResolution(ppi);
        } else {
            sendWrongNumberOfArgumentsError();
        }
    }
}

void InputHandler::tessSetRectangle() {
    if(checkInit()) {
        if(checkNumberOfArguments(4)) {
            int left = atoi(parsedCommand[1].c_str());
            int top = atoi(parsedCommand[2].c_str());
            int width = atoi(parsedCommand[3].c_str());
            int height = atoi(parsedCommand[4].c_str());
            myTess->SetRectangle(left, top, width, height);
        } else {
            sendWrongNumberOfArgumentsError();
        }
    }
}

void InputHandler::tessGetThresholdedImageScaleFactor() {
    if(checkInit()) {
        int result = myTess->GetThresholdedImageScaleFactor();
        cout << result << endl;
    }
}

void InputHandler::tessRecognize() {
    if(checkInit()) {
        myTess->Recognize(NULL);
    }
}

void InputHandler::tessRecognizeForChopTest() {
    if(checkInit()) {
        myTess->RecognizeForChopTest(NULL);
    }
}

void InputHandler::tessProcessPages() {
    if(checkInit()) {
        if(checkNumberOfArguments(3)) {
            string filename = parsedCommand[1];
            string retryConfig = parsedCommand[2];
            int timeout = atoi(parsedCommand[3].c_str());
            STRING textOut;
            STRING* textOutPt = &textOut;
            bool result = myTess->ProcessPages(filename.c_str(),retryConfig.c_str(),timeout,textOutPt);
            if(!result) {
                cerr << "ErrorTesseractCallFailed" << endl;
            } else {
                cout << textOut.string() << endl;
            }
        } else {
            sendWrongNumberOfArgumentsError();
        }
    }
}

void InputHandler::tessGetUTF8Text() {
    if(checkInit()) {
        char* result = myTess->GetUTF8Text();
        cout << result << endl;
        delete[] result;
    }
}

void InputHandler::tessGetHOCRText() {
    if(checkInit() && checkNumberOfArguments(1)) {
        int pageNumber = atoi(parsedCommand[1].c_str());
        char* result = myTess->GetHOCRText(pageNumber);
        cout << result << endl;
        delete[] result;
    }
}

void InputHandler::tessGetBoxText() {
    if(checkInit() && checkNumberOfArguments(1)) {
        int pageNumber = atoi(parsedCommand[1].c_str());
        char* result = myTess->GetBoxText(pageNumber);
        cout << result << endl;
        delete[] result;
    }
}

void InputHandler::tessGetUNLVText() {
    char* result = myTess->GetUNLVText();
    cout << result << endl;
    delete[] result;
}

void InputHandler::tessMeanTextConf() {
    if(checkInit()) {
        int result = myTess->MeanTextConf();
        cout << result << endl;
    }
}

void InputHandler::tessAllWordConfidences() {
    if(checkInit()) {
        int* result = myTess->AllWordConfidences();
        if(result != 0) {
            for(int i = 0; true; i++) {
                cout << result[i] << endl;
                if(result[i] == -1) break;
            }
        } else {
            cout << "-1" << endl;
        }
    } else {
        cout << "-1" << endl;
    }
}

void InputHandler::tessAdaptToWordStr() {
    if(checkInit() && checkNumberOfArguments(2)) {
        tesseract::PageSegMode* target = new tesseract::PageSegMode();
        *target = PSM_AUTO;
        bool parseResult = parser->getPageSegMode(parsedCommand[1], target);
        if(parseResult) {
            bool result = myTess->AdaptToWordStr(*target,parsedCommand[2].c_str());
            if(!result) {
                cerr << "ErrorWrongArgumentsNumber" << endl;
            }
        }
    }
}

void InputHandler::tessIsValidWord() {
    if(checkInit() && checkNumberOfArguments(1)) {
        int result = myTess->IsValidWord(parsedCommand[1].c_str());
        cout << result << endl;
    }
}

void InputHandler::tessGetTextDirection() {
    if(checkInit()) {
        int offset = 0;
        int* outOffset = &offset;
        float slope = 0;
        float* outSlope = &slope;
        bool result = myTess->GetTextDirection(outOffset, outSlope);
        if(result) {
            cout << offset << endl;
            cout << slope << endl;
        }
    }
}

void InputHandler::tessGetUniChar() {
    if(checkInit() && checkNumberOfArguments(1)) {
        int id = atoi(parsedCommand[1].c_str());
        cout << myTess->GetUnichar(id) << endl;
    }
}

void InputHandler::tessNumDawgs() {
    if(checkInit()) {
        cout << myTess->NumDawgs() << endl;
    }
}

void InputHandler::tessMakeTessOCRRow() {
    if(checkInit() && checkNumberOfArguments(4)) {
        float baseline = atof(parsedCommand[1].c_str());
        float xheight = atof(parsedCommand[2].c_str());
        float descender = atof(parsedCommand[3].c_str());
        float ascender = atof(parsedCommand[4].c_str());
        myTess->MakeTessOCRRow(baseline, xheight, descender, ascender);
    }
}

void InputHandler::tessGetOEMString() {
    if(checkInit()) {
        string target = "";
        string* tarPt = & target;
        bool result = parser->getOEMString(myTess->oem(), tarPt);
        if(result) {
            cout << target << endl;
        } else {
            cerr << "ErrorWrongArgumentsNumber" << endl;
        }
    }
}

void InputHandler::tessSetMinOrientationMargin() {
    if(checkInit() && checkNumberOfArguments(1)) {
        double margin = atof(parsedCommand[1].c_str());
        myTess->set_min_orientation_margin(margin);
    }
}

void InputHandler::tessFindLinesCreateBlockList() {
    if(checkInit()) {
        currentBlocks = myTess->FindLinesCreateBlockList();
    }
}

void InputHandler::tessDeleteBlockList() {
    if(checkInit()) {
        myTess->DeleteBlockList(currentBlocks);
    }
}


/*
 * Helper functions
 */
PIX* InputHandler::readImageToPix() {
    int charNum = atoi(parsedCommand[1].c_str());
    std::vector<char> ch_data;
    char byt;

    istream file(cin.rdbuf());
    for(int i = 0; i < charNum; i++) {
        file.get(byt);
        ch_data.push_back(byt);
    }
    cin.ignore(cin.rdbuf()->in_avail());
    //cerr << decode;
    size_t  size = ch_data.size();
    //    cerr << size << endl;
    l_uint8 *data;
    if ( (data = (l_uint8 *) malloc( size )) != NULL ) {
        try {
        memcpy(data, &(ch_data)[0], size);
        }
        catch (...) {
            throw "ExceptionMemcpy";
        }
    } else {
        fprintf(stderr,"Memory allocation error\n");
        exit(1);
    }
    PIX* retPix = pixReadMemPng(data, size);
    delete[] data;
    ch_data.clear();
    //    cerr << "executing pixReadMem" << endl;
    return retPix;
    /*
    if (false) {
        int charNum = atoi(parsedCommand[1].c_str());
        cerr << charNum << endl;
        istream sfile(cin.rdbuf());
        char* target = new char[charNum];
        for(int i = 0; i < charNum; i++) {
            sfile.get(target[i]);
        }
        cin.ignore(cin.rdbuf()->in_avail());
        //    cerr << target
        //    string st_data = base64_decode(target);
        //    cerr << st_data;
        string x = base64_decode(target);
                cerr << x << endl;
        l_uint8* xdata = (l_uint8*) malloc (sizeof(l_uint8)*x.length());
        memcpy(xdata, x.data(), x.length());
//        int imgSize = base64_decode(target, tarVec);
//        cerr << imgSize << endl;
        //    l_uint8 *xdata = new l_uint8[imgSize];
        //    memcpy(xdata, &tarVec[0], sizeof(l_uint8)*imgSize);
        cerr  << "PIX creation..." << endl;
        pixd = pixReadMem(xdata, x.length());
        if (pixd == NULL) {
            cerr << "Could not create PIX from stdin" << endl;
            exit(1);
        }
        cerr << "PIX created!" << endl;
        delete[] xdata;
    }*/
    /*
    if(false) {
        int imgSize = atoi(parsedCommand[1].c_str());
        istream sfile(cin.rdbuf());
        vector<char> ch_data;
        //sfile.get(byt);

        char byt;
        for(int i = 0; i < imgSize-1; i++) {
            //        if((i < 5) || (i > (imgSize-5))) cerr << i << byt << endl;
            sfile.get(byt);
            ch_data.push_back(byt);
//            cerr << byt;
        }

        //
        //    while (sfile.get(byt)) {
        //        ch_data.push_back(byt);
        //        cerr << byt;
        //    }
        //cerr << "hier!" << endl;
        cin.ignore(cin.rdbuf()->in_avail());
        cerr << ch_data.size() << endl;
        size_t  size = ch_data.size();
        l_uint8 *rdata;
        if ( (rdata = (l_uint8 *) malloc( sizeof(l_uint8)*size )) != NULL ) {
            memcpy(rdata, &(ch_data)[0], size);
        } else {
            cerr << "Memory allocation error" << endl;
            exit(1);
        }
        pixd = pixReadMem(rdata, size);
        if (pixd == NULL) {
            cerr << "Could not create PIX from stdin" << endl;
            //        exit(1);
        }
        delete[] rdata;
    }*/
    /*
    if (false) {
        //read file from harddisk for comparison
        FILE *file;
        file = fopen("/home/max/Arbeitsfläche/eng1.png", "rb");
        fseek (file , 0 , SEEK_END);
        size_t length=ftell (file);
        rewind (file);
        char* dstTmp = (char*) malloc (sizeof(char)*length);
        fread (dstTmp,1,length,file);
        fclose(file);

        double i = 0;
        while ((length - i) > 1) {
            cerr << dstTmp[(int) i];
            i++;
        }
        l_uint8* data = (l_uint8*) malloc (sizeof(l_uint8)*length);
        memcpy(data, dstTmp, length);
        PIX* pixa = pixReadMem(data,length);
        myTess->SetImage(pixa);
        cerr << myTess->GetUTF8Text();
        pixDestroy(&pixa);
        delete[] data;
     */
    /*
        //compare
//        if(size != length) {
//            cerr << "size sucks: " << length << " != " << size << endl;
//        }
//        else cerr << "size rocks" << endl;
//        int diff = 0;
//        for(size_t i = 0; i < length; i++) {
//            if((ch_data[i] != dstTmp[i])) {
//                if(diff == 0) diff = i;
//                //            cerr << ch_data[i] << " != " << dstTmp[i] << endl;
//            }
//        }
//        cerr << diff << endl;
//        delete[] dstTmp;
//        ch_data.clear();
    }
     */
}

void InputHandler::readImageData(const l_uint8 *dataConst) {
    //TODO buggy
    size_t imageSize = strtoul(parsedCommand[1].c_str(), 0, 0);
    int imageSizeInt = atoi(parsedCommand[1].c_str());
    cerr << imageSize << endl;
    cerr << imageSizeInt << endl;
    //ask for image
    l_uint8* data = new l_uint8[imageSizeInt];
    if(!silent) cout << "SubmitImagedata" << endl;
    char* imgBuff = new char[imageSizeInt];
    string imgBuffS = imgBuff;
    //Read image and store in buffer.
    for(int i = 0; i < imageSizeInt;) {
        char* tempBuff = new char[2048];
        cin.getline(tempBuff,2048);
        imgBuffS.append(tempBuff);
        i = imgBuffS.length();
        cerr << imgBuffS << endl;
        cerr << i << endl;
    }
    //cin.readsome(imgBuff, imageSizeInt);
    //cin.read(imgBuff, imageSize);
    cerr << imgBuff << endl;
    memcpy(data, imgBuff, imageSizeInt);
    dataConst = data;
}


//Checks for number of arguments, writes an error to cerr and returns false if wrong number.
bool InputHandler::checkNumberOfArguments(int expectedArguments){
    if(parsedCommand.size() == (expectedArguments + 1)) {
        return true;
    } else {
        return false;
    }
}

//Sends error message for wrong number of arguments
void InputHandler::sendWrongNumberOfArgumentsError() {
        cerr << "ErrorWrongArgumentsNumber" << endl;
}
//Checks if initiated and sends error if not
bool InputHandler::checkInit() {
    if(!isInit) {
        cerr << "ErrorNotInitialized" << endl;
        return false;
    }
    return true;
}

