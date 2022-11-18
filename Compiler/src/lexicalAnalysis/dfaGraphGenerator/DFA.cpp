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
            if(!is_in){closure->insert(t);stack.push(t);}
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


void DFA::create_inputs(vector<PostfixContainer> *rules){
    for (auto &it: *rules) {
        for (int i = 0 ; i < it.getPostFix().length() ; i++) {
            char ch = it.getPostFix()[i];
            if(ch !='|' && ch!='*' && ch!='+' && ch!=' ' ){
                chars.insert(ch);
            }else{
                for(int j = i-1 ; j >-1 ; j--){
                    if(it.getPostFix()[j]!=' ' ){
                        if(it.getPostFix()[j] == '\\'){
                            chars.insert(ch);
                        }
                        break;
                    }
                }
            }

        }
    }
}


vector<DFAstate *> DFA::build_DFA(){
    vector<DFAstate *> states;
    auto *first = new DFAstate();;
    first->closure.insert(start);
    epsilonClosure(&first->closure);

    for (auto &c: first->closure) {
        if (c->getAcceptance()) {
            first->acceptance = true;
            first->tokenName = c->getTokenName();
            break;
        }
    }
    states.push_back(first);
    for (int i = 0; i < states.size(); i++) {
        if (!states[i]->mark) {
            states[i]->mark = true;
        } else {
            continue;
        }
        for (set<char>::iterator a = chars.begin();a != chars.end(); a++){
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
                    states[i]->transitions[*a] = d;
                    newItem = false;
                    break;
                }
            }
            if (newItem) {
                for (auto &c: u->closure) {
                    if (c->getAcceptance()) {
                        u->acceptance = true;
                        break;
                    }
                }
                states.push_back(u);
                states[i]->transitions[*a] = (states.size() - 1);
            }
        }
    }
    return states;
}