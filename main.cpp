#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

static long int total;
static int empty, size;


int compute_sum(std::unordered_map<int, int> &rows, std::unordered_map<int, std::unordered_set<int>> &max_cols, const int &size, std::unordered_map<int, std::unordered_set<int>> &empties) {

  std::unordered_map<int, int>::iterator row_itr;
  int required = size - empty;
  for (row_itr = rows.begin(); row_itr != rows.end(); row_itr++) {
    int row = row_itr->first;
    int row_max = row_itr->second;
    if (!(max_cols[row_max].empty())) {
      std::unordered_set<int> &cols = max_cols[row_max];
      std::unordered_set<int> &row_empties = empties[row];
      for (int c : cols) {
        if (row_empties.count(c) == 0) {
          cols.erase(c);
          break;
        }
      }
    }
    if (row_max > 0) {
      required--;
      total -= row_max;
    }
  }
  // subtract each remaining col from total
  std::unordered_map<int, std::unordered_set<int>>::iterator col_itr;
  for (col_itr = max_cols.begin(); col_itr != max_cols.end(); col_itr++) {
    int col_max = col_itr->first;
    for (int col : col_itr->second) {
      if (col_max > 0) {
        total -= col_max;
        required--;
      }
    }
  }
  // every pos must have at least one box 
  total -= required;
  return total;
}

/*

transfers data from map
i.e 

col_max => max_cols

col_max
[
  0 : 70,
  1 : 60,
  2 : 70,
  3 : 50,
  4 : 50
]
max_cols
[
  70 : {0,2},
  60 : {1},
  50 : {3,4}
]

col_max values become max_cols keys
col_max keys become max_cols values

records empties for collision detection


*/


void swap_map(std::unordered_map<int, int> &col_max, std::unordered_map<int, std::unordered_set<int>> &max_cols) {
  std::unordered_map<int, int>::iterator itr;
  for (itr = col_max.begin(); itr != col_max.end(); itr++) {
    max_cols[itr->second].insert(itr->first);
  }
}

void build_constraints(const int &r,const int &c, std::unordered_map<int, int> &rows, std::unordered_map<int, int> &cols, std::unordered_map<int, std::unordered_set<int>> &empties) {
  int val;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      std::cin >> val;
      total += val;
      int &curr_row_max = rows[i]; //default initializer of int type is 0
      int &curr_col_max = cols[j];
      if (val > curr_col_max) {
        cols[j] = val;
      }
      if (val > curr_row_max) {
        rows[i] = val;
      }
      if (val == 0) {
        empties[i].insert(j);
        empty++;
      }
    }
  } 

}

int main() {
  int r, c;
  while (std::cin >> r) {
    std::cin >> c;
    total = 0;
    empty = 0;
    size = r * c;
    std::unordered_map<int, int> rows_max(r);
    std::unordered_map<int, int> cols_max(c);
    std::unordered_map<int, std::unordered_set<int>> empties; //collision detection
    std::unordered_map<int, std::unordered_set<int>> max_cols;
    build_constraints(r, c, rows_max, cols_max, empties);
    swap_map(cols_max, max_cols);
    std::cout << compute_sum(rows_max, max_cols, size, empties) << std::endl;
  }
}

