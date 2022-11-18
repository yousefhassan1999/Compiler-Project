#ifndef COMPILER_DFA_MINIMIZER_H
#define COMPILER_DFA_MINIMIZER_H

#include "DFA.h"

class DFAMinimizer {
private:
    vector<int> findEquivalence(DFA *dfa);
    vector<vector<int>> groupsList(vector<int> &group, int nGroups);
    DFA* mergeGroups(vector<int> &group, DFA *dfa);
    void removeDeadStates();
    int countGroups(vector<int> &group);
    bool equivalent(int s1, int s2, vector<int> &group, DFA *dfa);
public:
    DFA* minimize(DFA *dfa);
};


#endif //COMPILER_DFA_MINIMIZER_H
