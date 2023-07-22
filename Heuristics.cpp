//
// Created by jpricarte on 16/07/23.
//

#include "Heuristics.h"
#include <functional>
#include <cmath>

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

double Heuristics::best_improvement_tabu(Lop &lop, bool randomize) {
    int best_i=-1, best_j=-1;
    double best_delta=0;
    for (int i=0; i<lop.size(); i++) {
        if (tabu_memory[lop.permutation()[i]] < iterations) {
            int j = rand() % lop.size();
            double delta = lop.get_shift_cost(i, j);
            if (delta > best_delta) {
                best_delta = delta;
                best_i=i;
                best_j=j;
            }
        }
    }
    int increment = randomize ? min(int(random() % 10) + 1, lop.size()) : 0;
    tabu_memory[lop.permutation()[best_i]] = iterations + tabu_time + increment;
    tabu_memory[lop.permutation()[best_j]] = iterations + tabu_time + increment;
    lop.shift_and_update(best_i, best_j, best_delta);
    return best_delta;
}

Heuristics::Heuristics(int instance_size, int time_proportion) {
    tabu_memory = vector<int>(instance_size, 0);
    tabu_time = ceil(instance_size / time_proportion);
    iterations = 0;
}

Result Heuristics::tabu_search(Lop &lop, bool randomize) {
    int since_last_improvement = 0;
    int max_time = 3*lop.size();
    while (since_last_improvement < max_time) {
        since_last_improvement++;
        iterations++;
        double delta = best_improvement_tabu(lop, randomize);
        if (delta > 1)
            since_last_improvement = 0;
    }
    return Result {lop.obj_value(), iterations};
}
