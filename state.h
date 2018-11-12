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
        bool isInitial=false;
        bool isFinal=false;
        bool compuesto = false;

        // Constructors and destructor
        State(S _name, bool isInitial=false, bool isFinal=false);
        State(const State<A> &other);
        ~State();

        // Access methods
        S getName();
        void changeName(S new_name) {
            std::cout <<std::endl <<  name <<" changed to " << new_name;
            name = new_name;
        };

};

template <typename A>
State<A>::State(S _name, bool _isInit, bool _isFin) 
: name(_name), isInitial(_isInit), isFinal(_isFin){};

template <typename A>
State<A>::State(const State<A> &other){
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