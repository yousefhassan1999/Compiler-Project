#ifndef COMPILER_ERROR_LOGGER_H
#define COMPILER_ERROR_LOGGER_H

#include <string>
using namespace std;

class ErrorLogger {
public:
    static const string filePath;
    static void lexicalError(const string& msg);
    static void parsingError(const string& msg);
};


#endif //COMPILER_ERROR_LOGGER_H
