#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

#include <vector>
#include <map>

#include "node.h"
#include "edge.h"

using namespace std;

struct Traits {
	typedef string N;
	typedef int E;
};

template <typename Tr>
class Graph{
    public:
    	typedef typename Tr::N N;
        typedef typename Tr::E E;
        typedef Graph<Tr> self;
        typedef Node<self> node;
        typedef Edge<self> edge;
        typedef map<N, node*> NodeSeq;
        typedef vector<edge*> EdgeSeq;
        typedef typename NodeSeq::iterator NodeIte;
        typedef typename EdgeSeq::iterator EdgeIte;

    private:
        NodeSeq nodes; // Mapa de punteros de nodos <data (node name), node pointer>
        
        int sizeOfGraph[2]= {0,0}; // sizeOfGraph[0]: num de nodes -  sizeOfGraph[1]: num de edges


	    // Funciones auxiliares y utiles
	    void add_edge(edge someedge){
        	add_edge(someedge.nodes[0]->get_data(), someedge.nodes[1]->get_data(), someedge.get_peso(), someedge.get_dir());
        };

        EdgeIte remove_edge(node* vi, node* vf){
        	EdgeIte it;
        	for (auto it_edge = vi->edges.begin(); it_edge!=vi->edges.end(); ++it_edge){
				if ((*it_edge)->nodes[1]==vf) {
					it = vi->edges.erase(it_edge);
					delete *it_edge;
					break;
				}
			}
			return it;
        }

	public:

		// Constructores
		Graph(int size) : Graph(size, is_arithmetic<N>{}){};

		Graph(int size, true_type) { // int, float, char
			sizeOfGraph[0] = size;
			node* newnode;
			for (N i=0;i<size;++i){
				newnode=new node(i+65*(sizeof(N)==1));
				nodes.insert(pair <N, node*> (i+65*(sizeof(N)==1), newnode));
			}
		};

		Graph(int size, false_type) { // string
			sizeOfGraph[0] = size;
			node* newnode;
			for (char i=0;i<size;++i){
				newnode=new node(string(1, i+65));
				nodes.insert(pair <N, node*> (string(1, i+65), newnode));
			}
		};

		Graph(const Graph &other_graph) { // copy constructor
			nodes = other_graph.nodes;
			sizeOfGraph[0] = other_graph.sizeOfGraph[0];
			sizeOfGraph[1] = other_graph.sizeOfGraph[1];
		};


		// Metodos para debugging
		void print(){
			for (auto& thenode : nodes){
				cout<< "\nNodo " << thenode.first << ": ";
				for (auto& theedge : thenode.second->edges){
					cout << theedge->nodes[1]->get_data() << " ";
				}
			}
		};


		// Metodos de informacion basica
		int* size(){ return sizeOfGraph; };


		// Metodos fundamentales
		bool add_node(N node_name){
			if (nodes.find(node_name)!=nodes.end()) return false; // name taken
			node* newnode = new node(node_name);
			nodes.insert(pair<N, node*> (node_name, newnode));
			++sizeOfGraph[0];
			return true;
		};

		bool add_edge(N Vi, N Vf, E peso, bool dir){
			// Comprobar que los vertices existan
			if (!(nodes.count(Vi) && nodes.count(Vf)))
				return false;

			node* initial_node=nodes[Vi];
			node* final_node=nodes[Vf];
			// si el edge no tiene direccion, no hay nodo final ni inicial
			// (debe agregarse en la lista de edges de ambos nodos)

			edge* new_edge = new edge(initial_node,final_node,peso,dir);
			auto edge_in_edges = initial_node->edges.begin();

			// para mantener los edges ordenados en node.edges
			while (edge_in_edges!=initial_node->edges.end() && *new_edge>**edge_in_edges) ++edge_in_edges;

			if (initial_node->edges.empty() || *edge_in_edges==*initial_node->edges.end()) initial_node->edges.push_back(new_edge); // el nuevo edge debe ir al final
			else if (*new_edge==**edge_in_edges) return false; // hay otro edge con un mismo inicio y fin
			else initial_node->edges.insert(edge_in_edges, new_edge);

			++sizeOfGraph[1];
			return true;
		};

		bool remove_node(N node_name){
			if (nodes.find(node_name)==nodes.end()) return false; // not found
			node* to_remove = nodes[node_name];

			auto it_edge = to_remove->edges.begin();
			while (it_edge!=to_remove->edges.end()){
				it_edge = remove_edge((*it_edge)->nodes[0], (*it_edge)->nodes[1]);
			}
			delete to_remove;
			nodes.erase(node_name);
			return true;
		}

		bool remove_edge(N vi_name, N vf_name){
			if (nodes.find(vi_name)==nodes.end() || nodes.find(vf_name)==nodes.end()) return false; // not found
			node* vi = nodes[vi_name];
			node* vf = nodes[vf_name];

			remove_edge(vi, vf);
			return true;
		}

		// Algoritmos
		//TODO



		//Destructor
		~Graph(){
			auto it = nodes.begin();
			while (!nodes.empty()){
				delete (*it).second;
				it = nodes.erase(it);
			}
		}

};

typedef Graph<Traits> graph;

#endif