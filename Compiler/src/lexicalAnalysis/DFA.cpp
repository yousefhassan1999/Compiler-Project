//
// Created by Ahmed on 11/18/2022.
//

#include "DFA.h"
void epsilonClosure(unordered_set<NFAstate *> *closure) {
    stack<NFAstate *> stack;
    for (auto k: *closure) {
        stack.push(k);
    }
    while (!stack.empty()) {
        auto k = stack.top();
        stack.pop();
        unordered_map<char, vector<NFAstate *>> transitions = k->GetTransitions();
        vector<NFAstate *> vec = transitions[' '];
        for (auto &t: vec) {
            closure->insert(t);
            stack.push(t);
        }
    }
}



unordered_set<NFAstate *> move(unordered_set<NFAstate *> closure, char a) {
    unordered_set<NFAstate *> new_closure;
    for (auto k: closure) {
        unordered_map<char, vector<NFAstate *>> transitions = k->GetTransitions();
        vector<NFAstate *> vec = transitions[a];
        for (auto &t: vec) {
            new_closure.insert(t);
        }
    }
    return new_closure;
}



vector<DFAstate *> build_DFA(NFAstate start,vector<char> inputs){
    vector<DFAstate *> states;
    DFAstate *first = new DFAstate();;
    first->closure.insert(&start);
    epsilonClosure(&first->closure);

    for (auto &c: first->closure) {
        if (c->getAcceptance() == true) {
            first->Acceptence = true;
            break;
        }
    }
    states.push_back(first);
    for (int i = 0; i < states.size(); i++) {
        if (states[i]->mark == false) {
            states[i]->mark = true;
        } else {
            continue;
        }
        for (char a: inputs) {
            unordered_set<NFAstate *> new_closure = move(states[i]->closure, a);
            DFAstate *u = new DFAstate();
            u->closure = new_closure;
            if (u->closure.size() == 0) {
                continue;
            }
            bool newItem = true;
            for (int d = 0; d < states.size(); d++) {
                if (states[d]->closure == new_closure) {
                    states[i]->transitions[a] = states[d];
                    newItem = false;
                    break;
                }
            }
            if (newItem) {
                string s = "";
                for (auto &c: u->closure) {
                    if (c->getAcceptance() == true) {
                        u->Acceptence = true;
                        break;
                    }
                }
                states.push_back(u);
                states[i]->transitions[a] = states[states.size() - 1];
                DFAstate *ddd = states[i]->transitions[a];
            }
        }
    }

}