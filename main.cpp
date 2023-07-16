#include <iostream>
#include <chrono>
#include "Lop.h"
#include "Heuristics.h"

using namespace std;
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "usage: ./exec instance approach" << endl;
    }
    srand(0xc0ff3e);
    Lop instance(argv[1]);
    function<double(Lop&)> approach;
    if ("FI" == string(argv[2]))
        approach = Heuristics::first_improvement;
    else if ("BI" == string(argv[2]))
        approach = Heuristics::best_improvement;
    auto start = chrono::steady_clock::now();
    auto result = Heuristics::local_search(instance, approach);
    auto end = chrono::steady_clock::now();
    cout << "value\titer\ttime" << endl;
    cout << result.obj_value << "\t" << result.iterations << "\t" << float(chrono::duration_cast<chrono::milliseconds>(end-start).count())/1000 << endl;

    return 0;
}
