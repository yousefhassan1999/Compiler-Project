#ifndef COMPILER_DFA_MINIMIZER_H
#define COMPILER_DFA_MINIMIZER_H

#include "vectorDFA.h"

class DFAMinimizer {
private:
    static vector<int> findEquivalence(vectorDFA *dfa);
    static vector<int> assignGroups(vectorDFA *dfa);
    static vector<vector<int>> groupsList(vector<int> &group, int nGroups);
    static vectorDFA* mergeGroups(vector<int> &group, vectorDFA *dfa);
    static void removeDeadStates(vectorDFA *dfa, vector<int> &group);
    static int countGroups(vector<int> &group);
    static bool equivalent(int s1, int s2, vector<int> &group, vectorDFA *dfa);
public:
    static vectorDFA* minimize(vectorDFA *dfa);
};


#endif //COMPILER_DFA_MINIMIZER_H
