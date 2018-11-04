#ifndef STATE_H
#define STATE_H

template <typename A>
class State {
    public:
        typedef typename A::S S;
        typedef typename A::T T;
        typedef typename A::transition transition;
        typedef typename A::TransitionSeq TransitionSeq;

    private:
        S name;

    public:
        TransitionSeq transitions;

        State(S _name):name(_name){};
        // Métodos de acceso
        S getName(){ return name; }

        ~State(){
            while(!transitions.empty()) { delete transitions.back(); transitions.pop_back(); }
        }
};

#endif