#ifndef TRANSITION_H
#define TRANSITION_H

#include "state.h"
#include <iostream>

template <typename A>
class Transition {
    public:
        typedef typename A::T T;
        typedef typename A::state state;
        state* states[2];

    private:
        T symbol;
        
    public:
        // Constructor and destructor
        Transition(state* Vi,state* Vf,T symbol);
        ~Transition();

        // Access methods
        int getSymbol();

        // Overloads
        bool operator==(Transition<A> cmp);
        bool operator>(Transition<A> cmp) const;
        bool operator<(Transition<A> cmp) const;
};

template <typename A>
Transition<A>::Transition(state* Vi,state* Vf,T symbol):symbol(symbol){
    states[0]=Vi;
    states[1]=Vf;
}

template <typename A>
Transition<A>::~Transition(){
    states[0] = states[1] = nullptr;
}


template <typename A>
int Transition<A>::getSymbol(){ return symbol; }


template <typename A>
bool Transition<A>::operator==(Transition<A> cmp){
  return states[0] == cmp.states[0] &&
         states[1] == cmp.states[1] &&
         symbol == cmp.symbol;
}

template <typename A>
bool Transition<A>::operator>(Transition<A> cmp) const{
    // Compare symbols. If equal, compare states value
    return cmp.symbol==symbol? states[1]>cmp.states[1] : symbol>cmp.symbol;
}

template <typename A>
bool Transition<A>::operator<(Transition<A> cmp) const{
 return cmp.symbol==symbol? states[1]<cmp.states[1] : symbol<cmp.symbol;
}

#endif
