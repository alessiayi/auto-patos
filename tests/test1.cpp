#include <iostream>

#include "../state.h"
#include "../transition.h"
#include "../automata.h"

int main() {
  /* Autamata de la figura 4.8 pg. 131 del libro de Hopcroft */
  automata Auto(8);

  Auto.addTransition("A", "B", 0);
  Auto.addTransition("A", "F", 1);

  Auto.addTransition("B", "G", 0);
  Auto.addTransition("B", "C", 1);

  Auto.addTransition("C", "A", 0);
  Auto.addTransition("C", "C", 1);

  Auto.addTransition("D", "C", 0);
  Auto.addTransition("D", "G", 1);

  Auto.addTransition("E", "H", 0);
  Auto.addTransition("E", "F", 1);

  Auto.addTransition("F", "C", 0);
  Auto.addTransition("F", "G", 1);

  Auto.addTransition("G", "G", 0);
  Auto.addTransition("G", "E", 1);

  Auto.addTransition("H", "G", 0);
  Auto.addTransition("H", "C", 1);

  Auto.makeInitial("A");
  Auto.makeFinal("C");

  Auto.equivalenceN4();

  

  return 0;
}
