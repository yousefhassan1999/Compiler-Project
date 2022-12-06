//
// Created by Ahmed on 11/18/2022.
//

#include "DFA.h"


void DFA::epsilonClosure(unordered_set<NFAstate*> *closure) {
    stack<NFAstate *> stack;
    for (auto k: *closure) {
        stack.push(k);
    }
    while (!stack.empty()) {
        auto k = stack.top();
        stack.pop();
        unordered_map<char, vector<NFAstate*>> transitions = k->getTransitions();
        vector<NFAstate *> vec = transitions[' '];
        for (auto &t: vec) {
            bool is_in = closure->find(t) != closure->end();
            if(!is_in){
                closure->insert(t);
                stack.push(t);
            }
        }
    }
}




unordered_set<NFAstate*> DFA::move(unordered_set<NFAstate*> closure, char a) {
    unordered_set<NFAstate *> new_closure;
    for (auto k: closure) {
        unordered_map<char, vector<NFAstate *>> transitions = k->getTransitions();
        vector<NFAstate *> vec = transitions[a];
        for (auto &t: vec) {
            new_closure.insert(t);
        }
    }
    return new_closure;
}


vector<DFAstate *> DFA::build_DFA(){
    vector<DFAstate *> states;
    auto *first = new DFAstate();;
    first->closure.insert(start);
    epsilonClosure(&first->closure);

    unordered_set<string> pri;
    for (auto &c: first->closure) {
        if (c->getAcceptance()) {
            first->acceptance = true;
            pri.insert(c->getTokenName());
        }
    }
    if(!pri.empty()){
        if(pri.find("Keyword") != pri.end()){
            first->tokenName = "Keyword";
        }else if(pri.find("Punctuations") != pri.end()){
            first->tokenName = "Punctuations";
        }else{
            first->tokenName = *pri.begin();
        }
    }
    states.push_back(first);
    for (int i = 0; i < states.size(); i++) {
        if (!states[i]->mark) {
            states[i]->mark = true;
        } else {
            continue;
        }
        unordered_set<char> chars;
        for (auto itr : states[i]->closure )
        {
            for (auto c: itr->getTransitions()){
                if(c.first != ' ') {
                    chars.insert(c.first);
                }
            }
        }

        for (auto a = chars.begin();a != chars.end(); a++){
            unordered_set<NFAstate*> new_closure = move(states[i]->closure, *a);
            epsilonClosure(&new_closure);
            auto *u = new DFAstate();
            u->closure = new_closure;
            if (u->closure.empty()) {
                continue;
            }
            bool newItem = true;
            for (int d = 0; d < states.size(); d++) {
                if (states[d]->closure == new_closure) {
                    states[i]->transitions[*a] = toState(d);
                    newItem = false;
                    break;
                }
            }
            if (newItem) {
                unordered_set<string> pri;
                for (auto &c: u->closure) {
                    if (c->getAcceptance()) {
                        u->acceptance = true;
                        pri.insert(c->getTokenName());
                    }
                }
                if(!pri.empty()){
                    if(pri.find("Keyword") != pri.end()){
                        u->tokenName = "Keyword";
                    }else if(pri.find("Punctuations") != pri.end()){
                        u->tokenName = "Punctuations";
                    }else{
                        u->tokenName = *pri.begin();
                    }
                }
                states.push_back(u);
                states[i]->transitions[*a] = toState(states.size() - 1);
            }
        }
    }
    return states;
}