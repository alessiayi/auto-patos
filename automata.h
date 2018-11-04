// TODO: Solve error when using true_type and false_type constructors simultaneously

#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <iostream>

#include <vector>
#include <map>
#include <set>

#include "state.h"
#include "transition.h"

using namespace std;

struct Traits {
    typedef int S;
    typedef int T;
    typedef int Al; // Alphabet
};

template <typename Tr>
class Automata{
    public:
        typedef typename Tr::S S;
        typedef typename Tr::T T;
        typedef typename Tr::Al Al;
        typedef Automata<Tr> self;
        typedef State<self> state;
        typedef Transition<self> transition;
        typedef map<S, state*> StateSeq;
        typedef vector<transition*> TransitionSeq;
        typedef typename StateSeq::iterator NodeIte;
        typedef typename TransitionSeq::iterator TransitionIte;

    private:
        StateSeq states; // Map: <key, value> = <state.name, *state>
        int sizeOfAutomata[2] = {0,0}; // [0]: # states -  [1]: # transitions
        set<Al> alphabet = {0,1};

        // Auxiliary methods
        void addTransition(transition sometransition);
        TransitionIte removeTransition(state* vi, state* vf);

    public:
        // Constructors and destructor
        Automata(int size);
        Automata(int size, true_type);
        Automata(int size, false_type);
        Automata(const Automata &other_graph); // copy constructor
        ~Automata();

        // Debugging methods
        void print();

        // Access methods
        int* size();

        // Basic metodos 
        bool addState(S state_name);
        bool addTransition(S Vi, S Vf, T symbol);
        bool removeState(S state_name);
        bool removeTransition(S vi_name, S vf_name);
        bool setStateType(S state_name, int new_type);
        void setAlphabet(vector<Al>& alpha);

        // Algorithms
        //TODO
};
typedef Automata<Traits> automata;


/* 
Explicit template specializations 
(explicits specialization must go before implicit)
*/


template<>
automata::Automata(int size, true_type) { // int, float, char
    sizeOfAutomata[0] = size;
    state* newnode;
    for (S i=0;i<size;++i){
        newnode=new state(i+65*(sizeof(S)==1));
        states.insert(pair <S, state*> (i+65*(sizeof(S)==1), newnode));
    }
};

/*
template<>
automata::Automata(int size, false_type) { // string
    sizeOfAutomata[0] = size;
    state* newnode;
    for (char i=0;i<size;++i){
        newnode=new state(string(1, i+65));
        states.insert(pair <S, state*> (string(1, i+65), newnode));
    }
};
*/

template<>
automata::~Automata(){
    auto it = states.begin();
    while (!states.empty()){
        delete (*it).second;
        it = states.erase(it);
    }
};

template<>
automata::TransitionIte automata::removeTransition(state* vi, state* vf){
    automata::TransitionIte it;
    for (auto it_edge = vi->transitions.begin(); it_edge!=vi->transitions.end(); ++it_edge){
        if ((*it_edge)->states[1]==vf) {
            it = vi->transitions.erase(it_edge);
            delete *it_edge;
            break;
        }
    }
    return it;
};


/* 
Implicit template specializations
*/

template<>
automata::Automata(int size) : Automata(size, is_arithmetic<S>{}){};

template<>
automata::Automata(const Automata &other_graph) {
    // copy constructor
    states = other_graph.states;
    sizeOfAutomata[0] = other_graph.sizeOfAutomata[0];
    sizeOfAutomata[1] = other_graph.sizeOfAutomata[1];
};


template<>
bool automata::removeTransition(S vi_name, S vf_name){
    if (states.find(vi_name)==states.end() || states.find(vf_name)==states.end()) return false; // not found
    state* vi = states[vi_name];
    state* vf = states[vf_name];

    removeTransition(vi, vf);
    return true;
};

// Destructor above


template<>
void automata::print(){
    cout << "\nAlphabet:\t\t";
    for (auto& symbol: alphabet) cout << symbol << " ";


    // for (auto& thestates : states){
    // 	cout<< "\nNodo " << thestates.first << ": ";
    // 	for (auto& thetransition : thestates.second->transitions){
    // 		cout << thetransition->states[1]->getName() << " ";
    // 	}
    // }
};


template<>
int* automata::size(){ return sizeOfAutomata; };


template<>
bool automata::addState(S state_name){
    if (states.find(state_name)!=states.end()) return false; // getName taken
    state* newnode = new state(state_name);
    states.insert(pair<S, state*> (state_name, newnode));
    ++sizeOfAutomata[0];
    return true;
};


template<>
bool automata::addTransition(S Vi, S Vf, T symbol){
    // Comprobar que los vertices existan
    if (!(states.count(Vi) && states.count(Vf)))
        return false;

    state* initial_node=states[Vi];
    state* final_node=states[Vf];

    transition* new_edge = new transition(initial_node,final_node,symbol);
    auto edge_in_edges = initial_node->transitions.begin();

    // para mantener los transitions ordenados en state.transitions
    while (edge_in_edges!=initial_node->transitions.end() && *new_edge>**edge_in_edges) ++edge_in_edges;

    if (initial_node->transitions.empty() || *edge_in_edges==*initial_node->transitions.end()) initial_node->transitions.push_back(new_edge); // el nuevo transition debe ir al final
    else if (*new_edge==**edge_in_edges) return false; // hay otro transition con un mismo inicio y fin
    else initial_node->transitions.insert(edge_in_edges, new_edge);

    ++sizeOfAutomata[1];
    return true;
};

template<>
void automata::addTransition(transition sometransition){
    addTransition(sometransition.states[0]->getName(), sometransition.states[1]->getName(), sometransition.getSymbol());
};

// removeTransition() above

template<>
bool automata::removeState(S state_name){
    if (states.find(state_name)==states.end()) return false; // not found
    state* to_remove = states[state_name];

    auto it_edge = to_remove->transitions.begin();
    while (it_edge!=to_remove->transitions.end()){
        it_edge = removeTransition((*it_edge)->states[0], (*it_edge)->states[1]);
    }
    delete to_remove;
    states.erase(state_name);
    return true;
};

template<>
bool automata::setStateType(S state_name, int new_type){
    if (states.find(state_name)==states.end()) return false; // not found
    if (states[state_name]->type == new_type) return false;
    states[state_name]->type = new_type;
    return true;
};

template<>
void automata::setAlphabet(vector<Al>& alpha){
    copy(alpha.begin(), alpha.end(), inserter(alphabet, alphabet.end()));
}




#endif