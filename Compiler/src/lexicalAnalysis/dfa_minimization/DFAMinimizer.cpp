#include "DFAMinimizer.h"

vectorDFA* DFAMinimizer::minimize(vectorDFA *dfa) {
    vector<int> group = findEquivalence(dfa);
    return mergeGroups(group, dfa);
}

vector<int> DFAMinimizer::findEquivalence(vectorDFA *dfa) {
    vector<unordered_map<char, toState>> &table = dfa->getTransitionTable();
    size_t nStates = table.size();

    // divide into final and non-final groups
    vector<int> group(nStates);
    for (int i = 0; i < nStates; ++i) {
        group[i] = dfa->getStateInfo(i)->acceptance;
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

bool DFAMinimizer::equivalent(int s1, int s2, vector<int> &group, vectorDFA *dfa) {
    unordered_map<char, toState> &edges1 = dfa->getTransitionTable()[s1];
    unordered_map<char, toState> &edges2 = dfa->getTransitionTable()[s2];

    if(edges1.size() != edges2.size())
        return false;

    for(auto edge : edges1) {
        if(group[dfa->nextState(s1, edge.first)] != group[dfa->nextState(s2, edge.first)]) {
            return false;
        }
    }
    return true;
}

vectorDFA *DFAMinimizer::mergeGroups(vector<int> &group, vectorDFA *dfa) {
    int nGroup = countGroups(group);
    vectorDFA *minDFA = new vectorDFA(nGroup);
    vector<vector<int>> groups_list = groupsList(group, countGroups(group));

    for(auto g : groups_list) {
        int groupRep = g[0], newState = group[groupRep];
        // Add transitions
        for (auto edge : dfa->getTransitionTable()[groupRep]) {
            minDFA->addTransition(newState, edge.first, group[edge.second.get()]);
        }
        // Check for acceptance state within the group
        for (auto s : g) {
            StateInfo* info = dfa->getStateInfo(s);
            minDFA->addStateInfo(newState, info->acceptance, info->tokenName, info->tokenLexema);
        }
    }

    return minDFA;
}


