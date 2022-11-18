#include "DFAMinimizer.h"

DFA* DFAMinimizer::minimize(DFA *dfa) {
    vector<int> group = findEquivalence(dfa);
    return mergeGroups(group, dfa);
}

vector<int> DFAMinimizer::findEquivalence(DFA *dfa) {
    vector<vector<int>> &table = dfa->getTransitionTable();
    int nStates = table.size();

    // divide into final and non-final groups
    vector<int> group(nStates);
    for (int i = 0; i < nStates; ++i) {
        group[i] = dfa->getStateInfo(i).acceptance;
    }

    removeDeadStates();

    int nGroups = countGroups(group), oldNGroups;

    do {
        oldNGroups = nGroups;
        vector<int> tempGroup = group;
        vector<vector<int>> groups_list = groupsList(group, nGroups);

        for(auto g : groups_list) {
            vector<int> group_represent = {g.front()};
            for(auto state : g) {
                bool equiv_found = false;
                // Try to find equivalent group for the state
                for (auto rep : group_represent) {
                    if(equivalent(state, rep, tempGroup, dfa)) {
                        group[state] = group[rep];
                        equiv_found = true;
                        break;
                    }
                }
                // If not found create a new group
                if(!equiv_found) {
                    group[state] = nGroups++;
                    group_represent.push_back(state);
                }
            }
        }
    } while (nGroups != oldNGroups);

    return group;
}

void DFAMinimizer::removeDeadStates() {
    //TODO
}

int DFAMinimizer::countGroups(vector<int> &group) {
    int maxIdx = -1;
    for (int g : group)
        maxIdx = max(maxIdx, g);
    return maxIdx + 1;
}

vector<vector<int>> DFAMinimizer::groupsList(vector<int> &group, int nGroups) {
    vector<vector<int>> groups(nGroups);
    for (int s = 0; s < group.size(); ++s) {
        if(group[s] >= 0) {
            groups[group[s]].push_back(s);
        }
    }
    return groups;
}

bool DFAMinimizer::equivalent(int s1, int s2, vector<int> &group, DFA *dfa) {
    vector<vector<int>> &table = dfa->getTransitionTable();
    for(int i = 0; i < table[0].size(); ++i) {
        if(group[table[s1][i]] != group[table[s2][i]]) {
            return false;
        }
    }
    return true;
}

DFA *DFAMinimizer::mergeGroups(vector<int> &group, DFA *dfa) {
    return nullptr;
}


