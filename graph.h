#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

#include <vector>
#include <map>

#include "node.h"
#include "edge.h"

using namespace std;

struct Traits {
	typedef string S;
	typedef int T;
};

template <typename Tr>
class Automata{
    public:
    	typedef typename Tr::S S;
        typedef typename Tr::T T;
        typedef Automata<Tr> self;
        typedef State<self> state;
        typedef Transition<self> transition;
        typedef map<S, state*> StateSeq;
        typedef vector<transition*> TransitionSeq;
        typedef typename StateSeq::iterator NodeIte;
        typedef typename TransitionSeq::iterator TransitionIte;

    private:
        StateSeq states; // Mapa de punteros de estados <states.name, state pointer>
        int sizeOfAutomata[2]= {0,0}; // sizeOfAutomata[0]: num de states -  sizeOfAutomata[1]: num de transitions

	    // Funciones auxiliares y utiles
	    void addTransition(transition sometransition){
        	addTransition(sometransition.states[0]->getName(), sometransition.states[1]->getName(), sometransition.getSymbol());
        };

        TransitionSeq removeTransition(state* vi, state* vf){
        	TransitionSeq it;
        	for (auto it_edge = vi->transitions.begin(); it_edge!=vi->transitions.end(); ++it_edge){
				if ((*it_edge)->states[1]==vf) {
					it = vi->transitions.erase(it_edge);
					delete *it_edge;
					break;
				}
			}
			return it;
        }

	public:

		// Constructores
		Automata(int size) : Automata(size, is_arithmetic<S>{}){};

		Automata(int size, true_type) { // int, float, char
			sizeOfAutomata[0] = size;
			state* newnode;
			for (S i=0;i<size;++i){
				newnode=new state(i+65*(sizeof(S)==1));
				states.insert(pair <S, state*> (i+65*(sizeof(S)==1), newnode));
			}
		};

		Automata(int size, false_type) { // string
			sizeOfAutomata[0] = size;
			state* newnode;
			for (char i=0;i<size;++i){
				newnode=new state(string(1, i+65));
				states.insert(pair <S, state*> (string(1, i+65), newnode));
			}
		};

		Automata(const Automata &other_graph) { // copy constructor
			states = other_graph.states;
			sizeOfAutomata[0] = other_graph.sizeOfAutomata[0];
			sizeOfAutomata[1] = other_graph.sizeOfAutomata[1];
		};


		// Metodos para debugging
		void print(){
			for (auto& thestates : states){
				cout<< "\nNodo " << thestates.first << ": ";
				for (auto& thetransition : thestates.second->transitions){
					cout << thetransition->states[1]->getName() << " ";
				}
			}
		};


		// Metodos de informacion basica
		int* size(){ return sizeOfAutomata; };


		// Metodos fundamentales
		bool addState(S state_name){
			if (states.find(state_name)!=states.end()) return false; // getName taken
			state* newnode = new state(state_name);
			states.insert(pair<S, state*> (state_name, newnode));
			++sizeOfAutomata[0];
			return true;
		};

		bool addTransition(S Vi, S Vf, T symbol){
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

		bool removeState(S state_name){
			if (states.find(state_name)==states.end()) return false; // not found
			state* to_remove = states[state_name];

			auto it_edge = to_remove->transitions.begin();
			while (it_edge!=to_remove->transitions.end()){
				it_edge = removeTransition((*it_edge)->states[0], (*it_edge)->states[1]);
			}
			delete to_remove;
			states.erase(state_name);
			return true;
		}

		bool removeTransition(S vi_name, S vf_name){
			if (states.find(vi_name)==states.end() || states.find(vf_name)==states.end()) return false; // not found
			state* vi = states[vi_name];
			state* vf = states[vf_name];

			removeTransition(vi, vf);
			return true;
		}

		// Algoritmos
		//TODO



		//Destructor
		~Automata(){
			auto it = states.begin();
			while (!states.empty()){
				delete (*it).second;
				it = states.erase(it);
			}
		}

};

typedef Automata<Traits> automata;

#endif