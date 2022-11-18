#ifndef COMPILER_DFA_MINIMIZER_H
#define COMPILER_DFA_MINIMIZER_H

#include "vectorDFA.h"

class DFAMinimizer {
private:
    vector<int> findEquivalence(vectorDFA *dfa);
    vector<vector<int>> groupsList(vector<int> &group, int nGroups);
    vectorDFA* mergeGroups(vector<int> &group, vectorDFA *dfa);
    void removeDeadStates();
    int countGroups(vector<int> &group);
    bool equivalent(int s1, int s2, vector<int> &group, vectorDFA *dfa);
public:
    vectorDFA* minimize(vectorDFA *dfa);
};


#endif //COMPILER_DFA_MINIMIZER_H
