#ifndef TRANSITION_H
#define TRANSITION_H

#include "state.h"

template <typename A>
class Transition {
    public:
        typedef typename A::T T;
        typedef typename A::state state;
        state* states[2];

    private:
        T symbol;

    public:
        Transition(state* Vi,state* Vf,T symbol):symbol(symbol){
                states[0]=Vi;
                states[1]=Vf;
        }

        int getSymbol(){ return symbol; }
        bool operator==(Transition<A> cmp){
          return states[0] == cmp.states[0] &&
                 states[1] == cmp.states[1];
        }

        // Comparar por symbol
        // Si son iguales, comparar por el valor de states
        bool operator>(Transition<A> cmp) const{
          return cmp.symbol==symbol? states[1]>cmp.states[1] : symbol>cmp.symbol;
        }

        bool operator<(Transition<A> cmp) const{
         return cmp.symbol==symbol? states[1]<cmp.states[1] : symbol<cmp.symbol;
        }

        ~Transition(){
            states[0] = states[1] = nullptr;
        }
};

#endif
