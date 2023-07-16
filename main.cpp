#include <iostream>
#include <chrono>
#include "Lop.h"
#include "Heuristics.h"

using namespace std;
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Invalid input" << endl;
    }
    srand(0xc0ff33);
    Lop instance(argv[1]);

    auto start = chrono::steady_clock::now();
    auto result = Heuristics::local_search(instance, Heuristics::best_improvement);
    auto end = chrono::steady_clock::now();
    cout << "value\titer\ttime" << endl;
    cout << result.obj_value << "\t" << result.iterations << "\t" << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;

    return 0;
}
