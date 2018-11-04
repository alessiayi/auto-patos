#ifndef NODE_H
#define NODE_H

template <typename G>
class State {
    public:
        typedef typename G::S S;
        typedef typename G::T T;
        typedef typename G::transition transition;
        typedef typename G::TransitionSeq TransitionSeq;
    private:
        S name;

public:
        TransitionSeq transitions;

        State(S _name):name(_name){};
        // Métodos de acceso
        S getName(){ return name; }

        ~State(){
            while(!transitions.empty()) {
                delete transitions.back();
                transitions.pop_back();
            }
        }
};

#endif