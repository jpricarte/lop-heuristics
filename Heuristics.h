//
// Created by jpricarte on 16/07/23.
//

#ifndef LOP_HEURISTICS_H
#define LOP_HEURISTICS_H

#include "Lop.h"
#include <map>
#include <functional>

using namespace std;
struct Result {
    double obj_value;
    int iterations;
};

class Heuristics {
public:
    static double first_improvement(Lop& lop);
    static double  best_improvement(Lop& lop);

    static Result local_search(Lop &lop, const function<double(Lop &)>& get_neighbor);

};


#endif //LOP_HEURISTICS_H
