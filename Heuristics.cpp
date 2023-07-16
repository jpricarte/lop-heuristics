//
// Created by jpricarte on 16/07/23.
//

#include "Heuristics.h"
#include <random>
#include <functional>

double Heuristics::first_improvement(Lop &lop) {
    for (int i=0; i<lop.size(); i++) {
        int j = rand() % lop.size();
        double delta = lop.get_shift_cost(i, j);
        if (delta > 0) {
            lop.shift_and_update(i, j, delta);
            return delta;
        }
    }
    return 0;
}

double Heuristics::best_improvement(Lop& lop) {
    int best_i=-1, best_j=-1;
    double best_delta=0;
    for (int i=0; i<lop.size(); i++) {
        int j = rand() % lop.size();
        double delta = lop.get_shift_cost(i, j);
        if (delta > best_delta) {
            best_delta = delta;
            best_i=i;
            best_j=j;
        }
    }
    lop.shift_and_update(best_i, best_j, best_delta);
    return best_delta;
}

Result Heuristics::local_search(Lop &lop, const function<double(Lop &)>& get_neighbor) {
    int iterations = 0;
    bool improved = true;
    while (improved) {
        improved = false;
        iterations++;
        double delta = get_neighbor(lop);
        if (delta > 0)
            improved = true;
    }
    return Result {lop.obj_value(), iterations};
}
