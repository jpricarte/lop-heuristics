#include <iostream>
#include <chrono>
#include <filesystem>
#include "Lop.h"
#include "Constructive.h"

const int NUM_ITERATIONS = 30;

using namespace std;
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "usage: ./exec instance alpha" << endl;
        exit(1);
    }
    srand(0xc0ff3e);
    Lop instance(argv[1]);
    double alpha = stod(argv[2]);
    for (int i=1; i<=NUM_ITERATIONS; i++) {
        Lop lop(instance);
        auto result = Constructive::alpha_greedy_algorithm(lop, alpha);
        cout << filesystem::path(argv[1]).filename() << "\t"
             << alpha << "\t"
             << i << "\t"
             << result << endl;
    }
    return 0;
}
