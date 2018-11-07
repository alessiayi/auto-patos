# Autopatos: A state machine in C++
## Build your state machine
```c++
automata example(4); // Create a state machine with 4 states,  called 0 1 2 3

// Create a deep copy of our first state machine
automata example_copy(example); 
automata example_copy2 = example;
```
* `example` doesn't have a initial or final state
* `example_copy` and `example_copy2` will get states with the same name as `example` and the same transitions, alphabet and initial/final states.


```c++
example.addState(7);
example.addTransition(0,3,0); // State 0 to state 3 with 0
example.addTransition(1,2,1);

example.removeState(7);
example.removeTransition(1,2,1); 
```
* `addState` won't add a state with a repeated name
* `addTransition` won't add a transition if the states don't exist or if it's repeated (same initial state, final state and symbol)

```c++
example.makeInitial(0); // Set state 0 as initial state
example.makeFinal(2); // Set state 2 as final state
example.makeFinal(3); // Set state 3 as final state
example.makeInitial(4); // Change initial state to 4
example.makeIntermediate(1);

example.clearTypes(); // Reset all states to intermediate states
```
* Since a state machine can only have one initial state, `makeInitial` will demote current initial state to intermediate and set a new initial state
* If you `makeFinal` an initial state, it'll be overwritten

> Methods will return false if parameter is a non-existing state/transition or in any of the cases above

The default alphabet is {0,1}, but you can change it with...
```c++
example.setAlphabet({2,5,7}); // Pass a new alphabet in curly braces
```

## Admire your state machine

### print
<img src="https://i.stack.imgur.com/TwVxh.png" width="50%">

* With default alphabet..
```c++
example.print();
/*
 Alphabet |    0    |    1    |
----------|---------|---------|
->State 0 | 1        | 2    |
  State 1 | 0        | 2    |
 *State 2 | 2        | 2    |
*/
```
`->` Initial state </br>
`*`  Final state

You can use the output in markdown

 Alphabet |    0    |    1    |
----------|---------|---------|
->State 0 | 1        | 2    |
  State 1 | 0        | 2    |
 *State 2 | 2        | 2    |

* With another alphabet (for example: `{0,1,2}`) ..
```c++
example.print();
/*
Alphabet: 0 1 2 
State 0: [0]->1  [1]->2  
State 1: [0]->0  [1]->2  
State 2: [0]->2  [1]->2  
*/
```
`[0]->1` means _with 0 go to state 1_

* Formal print
```c++
example.formalPrint();
/*
3 0 1 2
0 0 1
0 1 2
1 0 0
1 1 2
2 0 2
2 1 2
*/
```
First line (states): `# of states`, `initial state`, `# of final states`, `final states` ... </br>
Next lines (transitions): `beginning`, `symbol`, `final` </br>
Note: A non-existing `initial state` will be represented with `-1` 

### size
``` c++
cout << "\nNumber of states: " <<example.size()[0];
cout << "\nNumber of transitions: " <<example.size()[1];
```
* `size()` will return an array with the number of states [0] and of transitions [1]


## Verify your state machine
`example.validateAFD()` will return `true` if `example` is a valid AFD.</br>
To be a valid AFD:
* Must have at least one final state
* Must have one initial state
* Each state must have as many transitions as symbols in the alphabet (ex.: if alphabet is {0,1} each state should have 2 transitions)
