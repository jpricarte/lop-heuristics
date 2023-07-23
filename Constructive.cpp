//
// Created by jpricarte on 22/07/23.
//

#include "Constructive.h"
#include <algorithm>
#include <cmath>


using namespace std;

bool ordering_function(const tuple<int, double>& i, const tuple<int, double>& j) {
    // Order in descending order
    return get<1>(i) > get<1>(j);
}

vector<tuple<int, double>> Constructive::calculate_sums(Lop &lop) {
    std::vector<tuple<int, double>> sums{};
    auto table = lop.lop_table();
    for (int i=0; i<lop.size(); i++) {
        double val = 0;
        for (int j=0; j<lop.size(); j++) {
            val += table[i][j] + table[j][i];
        }
        sums.emplace_back(i, val);
    }
    std::sort(sums.begin(), sums.end(), ordering_function);
    return sums;
}

Constructive::Selection Constructive::best_position(Lop &lop, const vector<int> &curr_permutation, const int new_elem) {
    auto &table = lop.lop_table();
    // Try emplace in every possible position
    double best_val = -1;
    int    best_pos = 0;
    for (int pos=0; pos<curr_permutation.size()+1; pos++) {
        double val = 0;
        // Calculate new column
        for (int i=0; i<pos; i++)
            val += table[curr_permutation[i]][new_elem];
        // Calculate new row
        for (int i=pos+1; i<curr_permutation.size(); i++)
            val += table[new_elem][curr_permutation[i]];
        if ((val > best_val) or (val == best_val and rand() > 0.5)) {
            best_val = val;
            best_pos = pos;
        }
    }
    return Selection{best_pos, best_val};
}

double Constructive::greedy_algorithm(Lop &lop) {
    vector<int> permutation{};
    auto sums = calculate_sums(lop);
    double curr_val = 0;
    int first_index = int(rand() % lop.size());
    permutation.push_back(get<0>(sums[first_index]));
    double val = 0;
    for (int i=0; i<lop.size(); i++) {
        if (i != first_index) {
            int element = get<0>(sums[i]);
            auto selected = best_position(lop, permutation, element);
            permutation.insert(permutation.begin()+selected.position, element);
            val += selected.delta;
        }
    }
    return val;
}

double Constructive::alpha_greedy_algorithm(Lop &lop, double alpha) {
    vector<int> permutation{};
    auto sums = calculate_sums(lop);
    double curr_val = 0;
    int first_index = int(rand() % lop.size());
    permutation.push_back(get<0>(sums[first_index]));
    std::remove(sums.begin(), sums.end(), sums[first_index]);
    double val = 0;
    for (int i=0; i < lop.size(); i++) {
        int available_elements = int(sums.size() * alpha);
        int selected_index = (alpha==0) ? 0 : int(rand() % available_elements);
        int element = get<0>(sums[selected_index]);
        auto selected = best_position(lop, permutation, element);
        permutation.insert(permutation.begin()+selected.position, element);
        std::remove(sums.begin(), sums.end(), sums[selected_index]);
        val += selected.delta;
    }
    return val;
}
