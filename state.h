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
        int type=0; // 0: normal state
                    // 1: initial state
                    // 2: final state

        // Constructors and destructor
        State(S _name, int _type=0);
        State(const State<A> &other);
        ~State();

        // Access methods
        S getName();

};

template <typename A>
State<A>::State(S _name, int _type) : name(_name), type(_type){};

template <typename A>
State<A>::State(const State<A> &other){
    type = other.type;
    name = other.name;
    for (auto& thetransition : other.transitions){
        transition* ptrans = new transition(thetransition->states[0], thetransition->states[1], thetransition->getSymbol());
        transitions.push_back(ptrans);
    }
}

template <typename A>
State<A>::~State(){
    while(!transitions.empty()){ 
        delete transitions.back();
        transitions.pop_back(); 
    } 
}

template <typename A>
typename A::S State<A>::getName(){ return name; };



#endif