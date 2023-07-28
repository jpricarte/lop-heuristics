//
// Created by jpricarte on 22/07/23.
//

#ifndef LOP_CONSTRUCTIVE_H
#define LOP_CONSTRUCTIVE_H


#include <vector>
#include <tuple>
#include "Lop.h"

class Constructive {
    struct Selection {
        int position;
        double delta;
    };

    static Selection best_position(Lop &lop, const std::vector<int> &curr_permutation, int new_elem);

public:
    static std::vector<std::tuple<int, double>> calculate_sums(Lop& lop);

    static double greedy_algorithm(Lop& lop);
    static double alpha_greedy_algorithm(Lop& lop, double alpha);
    static double grasp(Lop& lop, double alpha);
};


#endif //LOP_CONSTRUCTIVE_H
