#include <iostream>
#include <chrono> // measure execution time

#include "automata.h"

int main() {
    const int tries = 1000;

    cout << "Input:\n";
    automata test = Input();
    cout <<endl;
    // test.print();
    double average[5] {};

    for (int i=0; i<tries; ++i){
  
        // ------------- Test equivalenceN4 -------------
        auto start = chrono::high_resolution_clock::now(); 
        ios_base::sync_with_stdio(false);

        auto m = test.equivalenceN4();
        // test.printMatrix(m);

        auto end = chrono::high_resolution_clock::now();
        double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
        time_taken *= 1e-6;
        average[0]+=time_taken;
        // cout << "Equivalence N4 time: " << fixed << time_taken << setprecision(9) << " ms" << endl; 
        

        // ------------- Test equivalenceN2 -------------
        start = chrono::high_resolution_clock::now(); 
        ios_base::sync_with_stdio(false);
        
        auto m2 = test.equivalenceN2();
        // test.printMatrix(m2);

        end = chrono::high_resolution_clock::now();
        time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
        time_taken *= 1e-6;
        average[1]+=time_taken;
        // cout << "Equivalence N2 time: " << fixed << time_taken << setprecision(9) << " ms" << endl; 


        // ------------- Test Moore -------------
        start = chrono::high_resolution_clock::now(); 
        ios_base::sync_with_stdio(false);

        test.Moore();

        end = chrono::high_resolution_clock::now();
        time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
        time_taken *= 1e-6;
        average[2]+=time_taken;
        // cout << "Moore time: " << fixed << time_taken << setprecision(9) << " ms" << endl;

        // ------------- Test Hopcroft -------------
        start = chrono::high_resolution_clock::now(); 
        ios_base::sync_with_stdio(false);

        test.Hopcroft();

        end = chrono::high_resolution_clock::now();
        time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
        time_taken *= 1e-6;
        average[3]+=time_taken;
        // cout << "Hopcroft time: " << fixed << time_taken << setprecision(9) << " ms" << endl;

        cout <<"Try #" << i+1 << " done" << endl;
    }

    for (int i=0; i<5; ++i) average[i]/=tries;

    cout <<"\nNumber of tries: "<< tries << endl;
    cout << "Equivalence N4 time [ O(n^4) ]:\t" << fixed << average[0] << setprecision(9) << " ms" << endl; 
    cout << "Equivalence N2 time [ O(n^2) ]:\t" << fixed << average[1] << setprecision(9) << " ms" << endl; 
    cout << "Moore time [ O(n^2) ]:\t\t" << fixed << average[2] << setprecision(9) << " ms" << endl;
    cout << "Hopcroft time [ O(nlogn) ]:\t" << fixed << average[3] << setprecision(9) << " ms" << endl;



    // //Hopcroft
    // cout <<"\n\nHopcroft:";
    // test.Hopcroft(1).print();
    // cout <<"\n\nFormal Hopcroft:";
    // test.Hopcroft().formalPrint();
    

    // cout <<"\n\nMoore:";
    // test.Moore().print();
    // cout <<"\n\nFormal Moore:";
    // test.Moore().formalPrint();




  

  return 0;
}
