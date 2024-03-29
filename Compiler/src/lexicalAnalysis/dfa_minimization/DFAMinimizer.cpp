#include "DFAMinimizer.h"

vectorDFA* DFAMinimizer::minimize(vectorDFA *dfa) {
    vector<int> group = findEquivalence(dfa);
    return mergeGroups(group, dfa);
}

vector<int> DFAMinimizer::findEquivalence(vectorDFA *dfa) {
    vector<unordered_map<char, toState>> &table = dfa->getTransitionTable();
    vector<int> group = assignGroups(dfa);
    removeDeadStates(dfa, group);
    int nGroups = countGroups(group), oldNGroups;

    do {
        oldNGroups = nGroups;
        vector<int> tempGroup = group;
        vector<vector<int>> groups_list = groupsList(group, nGroups);

        for(auto g : groups_list) {
            if(g.size() < 2) continue;

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

vector<int> DFAMinimizer::assignGroups(vectorDFA *dfa) {
    size_t nStates = dfa->getTransitionTable().size();
    vector<int> group(nStates);
    int nGroups = 1;
    unordered_map<string, int> groupIdx;

    for (int i = 0; i < nStates; ++i) {
        StateInfo &info = dfa->getStateInfo(i);
        if(info.acceptance) {
            if (groupIdx.count(info.tokenName) == 0)
                groupIdx[info.tokenName] = nGroups++;
            group[i] = groupIdx[info.tokenName];
        }
        else {
            group[i] = 0;
        }
    }

    return group;
}

void explore(int state, vector<unordered_map<char, toState>> &table, unordered_set<int> &visited) {
    visited.insert(state);
    for (auto e : table[state]) {
        int s = e.second.get();
        if(visited.count(s) == 0) {
            explore(s, table, visited);
        }
    }
}

void DFAMinimizer::removeDeadStates(vectorDFA *dfa, vector<int> &group) {
    unordered_set<int> visited;
    explore(0, dfa->getTransitionTable(), visited);
    for (int i = 0; i < group.size(); ++i) {
        if(visited.count(i) == 0) {
            group[i] = -1;
        }
    }
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
    unordered_map<char, toState>
            &edges1 = dfa->getTransitionTable()[s1],
            &edges2 = dfa->getTransitionTable()[s2],
            &maxEdges = edges1.size() > edges2.size() ? edges1 : edges2;

    for(auto edge : maxEdges) {
        if(group[dfa->nextState(s1, edge.first)] != group[dfa->nextState(s2, edge.first)]) {
            return false;
        }
    }
    return true;
}

vectorDFA *DFAMinimizer::mergeGroups(vector<int> &group, vectorDFA *dfa) {
    int nGroup = countGroups(group);
    auto *minDFA = new vectorDFA(nGroup);
    vector<vector<int>> groups_list = groupsList(group, countGroups(group));

    for(auto g : groups_list) {
        int groupRep = g[0], newState = group[groupRep];
        // Add transitions
        for (auto edge : dfa->getTransitionTable()[groupRep]) {
            minDFA->addTransition(newState, edge.first, group[edge.second.get()]);
        }
        // Check for acceptance state within the group
        for (auto s : g) {
            StateInfo &info = dfa->getStateInfo(s);
            if(info.acceptance) {
                minDFA->addAcceptanceState(newState, info.tokenName);
                break;
            }
        }
    }

    return minDFA;
}


