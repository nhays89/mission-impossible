#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <unordered_set>
//using namespace std;


/*
Can represent data in the row or column of the input matrix.
Collects indexes for largest values.
Stores largest value in row or column.
*/
static long int total;
static int empty, size;
//class Node {
//public:
//  int val;
//  int pos;
//  bool valid;
//  Node *left;
//  Node *right;
//public:
//  Node() {
//    this->left = nullptr;
//    this->right = nullptr;
//  }
//};

//
//long int compute_sum(unordered_map<int, Obj> rows, unordered_map<int, Obj> cols, int *matrix, int r, int c) {
//  int val = 0;
//  long int sum = 0;
//  for (int i = 0; i < r; i++) {
//    Obj row_obj = rows[i];
//    for (int j = 0; j < c; j++) {
//      Obj col_obj = cols[j];
//      val = matrix[i * c + j];
//      if (val > 1 && 
//        col_obj.largest_indicies[0] != i &&
//        row_obj.largest_indicies[0] != j) {
//        sum += val - 1;
//      }
//      
//    }
//  }
//  return sum;
//}
//
//
//void compute_col_largest(unordered_map<int, Obj>& rows, unordered_map<int, Obj> &cols, int *matrix, int r, int c) {
//  unordered_map<int, Obj>::iterator it;
//  for (it = cols.begin(); it != cols.end(); it++) {
//    Obj &col = it->second;
//    bool found = false;
//    if (col.largest_indicies.size() > 1) {
//      for (int index : col.largest_indicies) {
//        Obj row = rows[index];
//        if (row.largest_indicies.size() == 1 && row.largest == col.largest) {
//          col.largest_indicies.clear();
//          col.largest_indicies.push_back(index);
//          found = true;
//          break;
//        }
//
//      }
//      if (!found) {
//        int first_index = col.largest_indicies[0];
//        col.largest_indicies.clear();
//        col.largest_indicies.push_back(first_index);
//      }
//    } //else if size is 1 ignore
//  }
//}
//
//void compute_row_largest(unordered_map<int, Obj> &rows, unordered_map<int, Obj> &cols, int *matrix, int r, int c) {
//  unordered_map<int, Obj>::iterator it;
//  for (it = rows.begin(); it != rows.end(); it++) { //isolate each row's largest value, if multiple indexes with largest value, select an index where the col is largest, if none, choose arbitrarily
//    Obj &row = it->second;
//    bool found = false;
//    int row_size = row.largest_indicies.size();
//
//    if (row_size > 1) {
//      for (int i : row.largest_indicies) {
//        Obj col = cols[i];
//        int col_size = col.largest_indicies.size();
//        if (col_size == 1 && col.largest == row.largest) { //if largest in col
//          int largest_index = i;
//          row.largest_indicies.clear();
//          row.largest_indicies.push_back(largest_index);
//          found = true;
//          break;					
//        }
//      }
//      if (!found) { //if none were largest in col, grab first one in set and make it largest in row
//        int first_index = row.largest_indicies[0];
//        row.largest_indicies.clear();
//        row.largest_indicies.push_back(first_index);
//      }
//    } //else if size is 1 then we already have largest single index
//  }
//
//}

//Node * find_BST(Node * root, int val) {
//  bool found = false;
//  Node *node = nullptr;
//  while (root && !found) {
//    if (val > root->val) {
//      root = root->right;
//    }
//    else if (val < root->val) {
//      root = root->left;
//    }
//    else {
//      if (root->valid) {   
//        found = true;
//        node = root;
//      }
//      else {
//        root = root->left;
//      }
//    }
//  }
//  return node;
//}
//
//
//void sum_BST(Node * col_root, long int total) {
//  if (!col_root) {
//    return;
//  }
//  else {
//    sum_BST(col_root->left, total);
//    sum_BST(col_root->right, total);
//    total += col_root->val;
//  }
//}




//create a node for each entry in the map
//add the node to a BST.
//Node * gen_BST(unordered_map<int, int> &map, vector<Node> &nodes) {
//  unordered_map<int, int>::iterator itr;
//  int i;
//  Node * const root = &(nodes[0]);
//  Node *next, *parent;
//  itr = map.begin();
//  for (++itr, i = 1; itr != map.end() && i < nodes.size(); ++itr, ++i) {
//    Node *node = &(nodes[i]);
//    node->val = itr->second;
//    node->pos = itr->first;
//    next = root;
//    while (next) {
//      parent = root;
//      if (node->val > next->val) {
//        if (!(next->right)) {
//          next->right = node;
//        }
//        next = next->right;
//      }
//      else {
//        if (!(next->left)) {
//          next->left = node;
//        }
//        next = next->left;
//      }
//    }
//  }
//  return root;
//}



void compute_sum(std::unordered_map<int, int> &rows, std::unordered_map<int, std::vector<int>> &cols_max, const int &size) {

  std::unordered_map<int, int>::iterator row_itr;
  int required = size - empty;
  for (row_itr = rows.begin(); row_itr != rows.end(); row_itr++) {
    int row = row_itr->first;
    int row_max = row_itr->second;
    if (!(cols_max[row_max].empty())) {
      cols_max[row_max].pop_back();
    }
    if (row_max > 0) {
      required--;
      total -= row_max;
    }
  }
  // subtract each remaining col from total
  std::unordered_map<int, std::vector<int>>::iterator col_itr;
  for (col_itr = cols_max.begin(); col_itr != cols_max.end(); col_itr++) {
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

*/


void swap_map(std::unordered_map<int, int> &col_max, std::unordered_map<int, std::vector<int>> &max_cols) {
  std::unordered_map<int, int>::iterator itr;
  for (itr = col_max.begin(); itr != col_max.end(); itr++) {
    max_cols[itr->second].push_back(itr->first);
  }
}

void build_constraints(const int &r,const int &c, std::unordered_map<int, int> &rows, std::unordered_map<int, int> &cols) {
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

    std:: unordered_map<int, int> rows_max(r);
    std::unordered_map<int, int> cols_max(c);
    std::unordered_map<int, std::vector<int>> max_cols;
    build_constraints(r, c, rows_max, cols_max);
    swap_map(cols_max, max_cols);
    compute_sum(rows_max, max_cols, size);
  }
}


