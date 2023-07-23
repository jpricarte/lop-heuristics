#include <iostream>
#include <chrono>
#include <filesystem>
#include "Lop.h"
#include "Heuristics.h"

const int NUM_ITERATIONS = 5;

using namespace std;
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "usage: ./exec instance tabu_proportion" << endl;
        exit(1);
    }
    srand(0xc0ff3e);
    Lop instance(argv[1]);
    Heuristics heuristics(instance.size(), stoi(argv[2]));
    // Fixed tenure
    for (int i=0; i<NUM_ITERATIONS; i++) {
        Lop lop(instance);
        auto result = heuristics.tabu_search(lop);
        cout << filesystem::path(argv[1]).filename() << "\t"
             << "F\t"
             << argv[2] << "\t"
             << i+1 << "\t"
             << result.obj_value << endl;
    }
    // Random Tenure
    for (int i=0; i<NUM_ITERATIONS; i++) {
        Lop lop(instance);
        auto result = heuristics.tabu_search(lop, true);
        cout << filesystem::path(argv[1]).filename() << "\t"
             << "R\t"
             << argv[2] << "\t"
             << i+1 << "\t"
             << result.obj_value << endl;
    }
    // Local Search
    for (int i=0; i<NUM_ITERATIONS; i++) {
        Lop lop(instance);
        auto result = Heuristics::local_search(lop, Heuristics::best_improvement);
        cout << filesystem::path(argv[1]).filename() << "\t"
             << "BI\t"
             << argv[2] << "\t"
             << i+1 << "\t"
             << result.obj_value << endl;
    }
    return 0;
}
