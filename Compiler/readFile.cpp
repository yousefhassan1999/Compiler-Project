#include <iostream>
#include <fstream>
#include <string>
#include "readFile.h"

using namespace std;

void ReadFileContaint (string Path) {
    string myText;
    ifstream MyReadFile(Path);
    while (getline (MyReadFile, myText)) {
      cout << myText<<"\n";
    }
    MyReadFile.close();
}
