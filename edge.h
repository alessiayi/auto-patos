#ifndef EDGE_H
#define EDGE_H

#include "node.h"

template <typename G>
class Transition {
    public:
        typedef typename G::T T;
        typedef typename G::state state;
        state* states[2];

    private:
        T symbol;

public:
    Transition(state* Vi,state* Vf,T symbol):symbol(symbol){
            states[0]=Vi;
            states[1]=Vf;
    }

    int getSymbol(){ return symbol; }
    bool operator==(Transition<G> cmp){
      return states[0] == cmp.states[0] &&
             states[1] == cmp.states[1];
    }

    // Comparar por symbol
    // Si son iguales, comparar por el valor de nodos
    bool operator>(Transition<G> cmp) const{
      return cmp.symbol==symbol? states[1]>cmp.states[1] : symbol>cmp.symbol;
    }

    bool operator<(Transition<G> cmp) const{
     return cmp.symbol==symbol? states[1]<cmp.states[1] : symbol<cmp.symbol;
    }

    ~Transition(){
        states[0] = states[1] = nullptr;
    }
};

#endif
