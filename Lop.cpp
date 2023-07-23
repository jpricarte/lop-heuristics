//
// Created by jpricarte on 16/07/23.
//

#include "Lop.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <bits/stl_vector.h>

using namespace std;

Lop::Lop(const vector<vector<double>>& instance) {
    _permutation = vector<int>();
    for (int i=0; i<instance.size(); i++) {
        _permutation.push_back(i);
        _lop_table.emplace_back(instance.size());
        for(int j=0; j<instance.size(); j++) {
            _lop_table[i][j] = instance[i][j];
            if (i < j)
                _obj_value += instance[i][j];
        }
    }
    _size = int(instance.size());
}

Lop::Lop(const std::string& file_name) {
    string line;
    ifstream file_stream(file_name);
    if (!file_stream.is_open()) {
        cerr << "Lop::Lop: Unable to open " << file_name << endl;
        throw exception();
    }
    // initialize size and obj_value
    getline(file_stream, line);
    _size = stoi(line);
    _obj_value = 0;
    // For each line, read the values in columns
    int row = 0;
    while(getline(file_stream, line)) {
        stringstream line_stream(line);
        // Add row
        _lop_table.emplace_back();
        // Iterate over col
        int col = 0;
        string raw_val;
        while(line_stream >> raw_val) {
            double val = stod(raw_val);
            _lop_table[row].push_back(val);
            if (col > row) {
                _obj_value += val;
            }
            col++;
        }
        _permutation.push_back(row);
        row++;
    }
}

ostream &operator<<(ostream &os, const Lop &lop) {
    for (auto& line : lop._lop_table) {
        for (auto val : line) {
            os << val << " ";
        }
        os << endl;
    }
    return os;
}

double Lop::get_shift_cost(int index_bef, int index_aft) {
    if (index_bef < index_aft)
        return get_shift_right_cost(index_bef, index_aft);
    else if (index_bef > index_aft)
        return get_shift_left_cost(index_bef, index_aft);
    else
        return 0;
}

double Lop::get_shift_right_cost(int index_bef, int index_aft) {
    return get_shift_col_cost(index_bef, index_aft, RIGHT)
         - get_shift_row_cost(index_bef, index_aft, RIGHT);
}

double Lop::get_shift_left_cost(int index_bef, int index_aft) {
    return get_shift_row_cost(index_aft, index_bef, LEFT)
         - get_shift_col_cost(index_aft, index_bef, LEFT);
}

double Lop::get_shift_col_cost(int index_left, int index_right, Direction direction) {
    int c = (direction == RIGHT) ? index_left : index_right;
    double delta = 0.0;
    for (int r=index_left; r<index_right; r++) {
        delta += _lop_table[r][c];
    }
    return delta;
}

double Lop::get_shift_row_cost(int index_left, int index_right, Direction direction) {
    int r = (direction == RIGHT) ? index_left : index_right;
    double delta = 0.0;
    for (int c=index_left; c < index_right; c++) {
        delta += _lop_table[r][c];
    }
    return delta;
}

void Lop::make_shift(int index_bef, int index_aft) {
    if (index_bef < index_aft) {
        make_shift_col(index_bef, index_aft, RIGHT);
        make_shift_row(index_bef, index_aft, RIGHT);
        make_shift_permutation(index_bef, index_aft, RIGHT);
    }
    else if (index_bef > index_aft) {
        make_shift_col(index_bef, index_aft, LEFT);
        make_shift_row(index_bef, index_aft, LEFT);
        make_shift_permutation(index_bef, index_aft, LEFT);
    }
}

void Lop::make_shift_col(int index_bef, int index_aft, Lop::Direction direction) {
    if (direction==RIGHT) {
        for (int row=0; row<_size; row++) {
            auto begin = _lop_table[row].begin() + index_bef;
            auto end = _lop_table[row].begin() + index_aft + 1;
            rotate(begin, begin+1, end);
        }
    }
    else {
        for (int row=0; row<_size; row++) {
            auto begin = _lop_table[row].rend() - index_bef - 1;
            auto end = _lop_table[row].rend() - index_aft;
            rotate(begin, begin+1, end);
        }
    }
}

void Lop::make_shift_row(int index_bef, int index_aft, Lop::Direction direction) {
    if (direction==RIGHT) {
        auto begin = _lop_table.begin() + index_bef;
        auto end = _lop_table.begin() + index_aft + 1;
        rotate(begin, begin+1, end);
    }
    else {
        auto begin = _lop_table.rend() - index_bef - 1;
        auto end = _lop_table.rend() - index_aft;
        rotate(begin, begin+1, end);
    }
}

void Lop::make_shift_permutation(int index_bef, int index_aft, Lop::Direction direction) {
    if (direction==RIGHT) {
        auto begin = _permutation.begin()+index_bef;
        auto end = _permutation.begin()+index_aft+1;
        rotate(begin, begin+1, end);
    }
    else {
        auto begin = _permutation.rend()-index_bef-1;
        auto end = _permutation.rend()-index_aft;
        rotate(begin, begin+1, end);
    }
}

void Lop::shift_and_update(int index_bef, int index_aft) {
    _obj_value += get_shift_cost(index_bef, index_aft);
    make_shift(index_bef, index_aft);
}

void Lop::shift_and_update(int index_bef, int index_aft, double delta) {
    _obj_value += delta;
    make_shift(index_bef, index_aft);
}

void Lop::rebuild_instance(vector<int> permutation) {
    vector<vector<double>> new_lop_table{};
    for (int i : permutation) {
        new_lop_table.emplace_back();
        for (int j : permutation) {
            new_lop_table.end()->push_back(_lop_table[i][j]);
        }
    }
    _lop_table = new_lop_table;
    _permutation = permutation;
}
