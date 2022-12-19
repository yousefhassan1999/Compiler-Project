#include "ErrorLogger.h"
#include <fstream>

const string ErrorLogger::filePath = "../errors.txt";

void ErrorLogger::lexicalError(const string &msg) {
    ofstream logFile;
    logFile.open(filePath, std::ios_base::app);
    logFile << "[Lexical Error] " << msg << endl;
    logFile.close();
}

void ErrorLogger::parsingError(const string &msg) {
    ofstream logFile;
    logFile.open(filePath, std::ios_base::app);
    logFile << "[Parsing Error] " << msg << endl;
    logFile.close();
}
