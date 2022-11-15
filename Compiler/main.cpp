#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "lexicalRules.h"
#include "lexicalGenerator.h"

using namespace std;
#include <iostream>
#include <vector>
#include <unordered_map>

//struct Pos {
//    int row;
//    int col;
//    Pos() { }
//    Pos(int row, int col){
//        this->row = row;
//        this->col = col;
//    }
//    bool operator==(const Pos& otherPos) const{
//        if (this->row == otherPos.row && this->col == otherPos.col) return true;
//        else return false;
//    }
//    struct HashFunction{
//        size_t operator()(const Pos& pos) const{
//            size_t rowHash = std::hash<int>()(pos.row);
//            size_t colHash = std::hash<int>()(pos.col) << 1;
//            return rowHash ^ colHash;
//        }
//    };
//};
//
//int main(void){
//    std::unordered_map<Pos, int, Pos::HashFunction> umap;
//    // at row 1, col 2, set value to 5
//    umap[Pos(1, 2)] = 5;
//    // at row 3, col 4, set value to 10
//    umap[Pos(3, 4)] = 10;
//    // print the umap
//    std::cout << "\n";
//    for (auto& element : umap){
//        std::cout << "( " << element.first.row << ", " << element.first.col << " ) = " << element.second << "\n";
//    }
//    std::cout << "\n";
//    return 0;
//}
int main () {
    LexicalGenerator ob;
    ob.GetLexicalRules().ReadFileContaint("D:\\fourth_year\\first term\\Compiler\\Assignments\\Compiler-Project\\Compiler\\lexical rules.txt");
    ob.GenerateNFA();
    /*LexicalRules ob;
    ob.ReadFileContaint("lexical rules.txt");
    vector<string> KeyWords = ob.GetLexicalRules().GetKeyWords();
    vector<string> Punctuations = ob.GetLexicalRules().GetPunctuations();
    vector<string> RegularDefinitions = ob.GetLexicalRules().GetRegularDefinitions();
    vector<string> RegularExpressions = ob.GetLexicalRules().GetRegularExpressions();

    cout << "RegularDefinitions\n";
    for (auto it = RegularDefinitions.begin(); it != RegularDefinitions.end(); ++it)
        cout << *it << "\n";
    cout << "Punctuations\n";
    for (auto it = Punctuations.begin(); it != Punctuations.end(); ++it)
        cout << *it << "\n";
    cout << "KeyWords\n";
    for (auto it = ob.GetLexicalRules().GetKeyWords().begin(); it != ob.GetLexicalRules().GetKeyWords().end(); ++it)
        cout << *it << "\n";
    cout << "RegularExpressions\n";
    for (auto it = RegularExpressions.begin(); it != RegularExpressions.end(); ++it)
        cout << *it << "\n";*/
    return 0;
}
