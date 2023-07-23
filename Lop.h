//
// Created by jpricarte on 16/07/23.
//

#ifndef LOP_LOP_H
#define LOP_LOP_H

#include <vector>
#include <string>
#include <ostream>

class Lop {
private:
    enum Direction {
        LEFT,
        RIGHT
    };

    int _size;
    std::vector<int> _permutation;
    std::vector<std::vector<double>> _lop_table;
    double _obj_value;

    double get_shift_right_cost(int index_bef, int index_aft);
    double get_shift_left_cost(int index_bef, int index_aft);
    double get_shift_col_cost(int index_left, int index_right, Direction direction);
    double get_shift_row_cost(int index_left, int index_right, Direction direction);

    void make_shift(int index_bef, int index_aft);
    void make_shift_col(int index_bef, int index_aft, Direction direction);
    void make_shift_row(int index_bef, int index_aft, Direction direction);
    void make_shift_permutation(int index_bef, int index_aft, Direction direction);

public:
    Lop(const std::vector<std::vector<double>>& instance);
    Lop(const std::string& file_name);

    inline int size() const { return _size; }
    inline double obj_value() const { return _obj_value; };
    inline std::vector<int> permutation() const { return _permutation; };
    inline std::vector<std::vector<double>> const lop_table() { return _lop_table; };

    double get_shift_cost(int index_bef, int index_aft);
    void  shift_and_update(int index_bef, int index_aft);
    void  shift_and_update(int index_bef, int index_aft, double delta);
    void  rebuild_instance(std::vector<int> permutation);

    friend std::ostream &operator<<(std::ostream &os, const Lop &lop);
};


#endif //LOP_LOP_H
