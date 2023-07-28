#include <iostream>
#include <filesystem>
#include "Lop.h"
#include "Constructive.h"
#include "Heuristics.h"

const int NUM_ITERATIONS = 30;

using namespace std;
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "usage: ./exec instance alpha" << endl;
        exit(1);
    }
    Lop instance(argv[1]);
    double alpha = stod(argv[2]);
    // Constructive
    srand(0xc0ff3e);
    for (int i=1; i<=NUM_ITERATIONS; i++) {
        Lop lop(instance);
        auto result = Constructive::greedy_algorithm(lop);
        cout << filesystem::path(argv[1]).filename() << "\t"
             << "G" << "\t"
                    << "\t"
             << result << endl;
    }
    // Constructive Randomized
    srand(0xc0ff3e);
    for (int i=1; i<=NUM_ITERATIONS; i++) {
        Lop lop(instance);
        auto result = Constructive::alpha_greedy_algorithm(lop, alpha);
        cout << filesystem::path(argv[1]).filename() << "\t"
             << "AG" << "\t"
             << alpha << "\t"
             << result << endl;
    }
    // GRASP
    srand(0xc0ff3e);
    for (int i=1; i<=NUM_ITERATIONS; i++) {
        Lop lop(instance);
        auto result = Constructive::grasp(lop, alpha);
        cout << filesystem::path(argv[1]).filename() << "\t"
             << "GR" << "\t"
             << alpha << "\t"
             << result << endl;
    }
    return 0;
}
