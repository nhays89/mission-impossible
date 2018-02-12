#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

static const int MAX = 100;

/*
Can represent data in the row or column of the input matrix.
Collects indexes for largest values.
Stores largest value in row or column.
*/
class Vector {
  public: 
    vector<int> largest_indicies;
    int largest;
  public: 
    Vector(size_t size, size_t largest, int values[]) {
      largest = largest;
      largest_indicies.resize(size);
      copy(values, values + size, largest_indicies.begin());
    };
};

long int compute_sum(unordered_map<int, Vector> rows, unordered_map<int, Vector> cols, int *matrix, int r, int c) {
  int val = 0;
  long int sum = 0;
  for (int i = 0; i < r; i++) {
    Vector row_obj = rows[i];
    for (int j = 0; j < c; j++) {
      Vector col_obj = cols[j];
      val = matrix[i * c + j];
      if (val > 1 && 
        col_obj.largest_indicies[0] != i &&
        row_obj.largest_indicies[0] != j) {
        sum += val - 1;
      }
      
    }
  }
  return sum;
}


void compute_col_largest(unordered_map<int, Vector> rows, unordered_map<int, Vector> cols, int *matrix, int r, int c) {
  unordered_map<int, Vector>::iterator it;
  for (it = cols.begin(); it != cols.end(); it++) {
    Vector col = it->second;
    bool found = false;
    if (col.largest_indicies.size() > 1) {
      for (int index : col.largest_indicies) {
        Vector row = rows[index];
        if (row.largest_indicies.size() == 1 && row.largest == col.largest) {
          col.largest_indicies.clear();
          col.largest_indicies.push_back(index);
          found = true;
          break;
        }

      }
      if (!found) {
        int first_index = col.largest_indicies[0];
        col.largest_indicies.clear();
        col.largest_indicies.push_back(first_index);
      }
    } //else if size is 1 ignore
  }
}

void compute_row_largest(unordered_map<int, Vector> rows, unordered_map<int, Vector> cols, int *matrix, int r, int c) {
  unordered_map<int, Vector>::iterator it;
  for (it = rows.begin(); it != rows.end(); it++) { //isolate each row's largest value, if multiple indexes with largest value, select an index where the col is largest, if none, choose arbitrarily
    Vector row = it->second;
    bool found = false;
    int row_size = row.largest_indicies.size();

    if (row_size > 1) {
      for (int i = 0; i < row_size; i++) {
        Vector col = cols[i];
        int col_size = col.largest_indicies.size();
        if (col_size == 1 && col.largest == row.largest) { //if largest in col
          row.largest_indicies.clear();
          row.largest_indicies.push_back(i);
          found = true;
          break;					
        }
      }
      if (!found) { //if none were largest in col, grab first one in set and make it largest in row
        int first_index = row.largest_indicies[0];
        row.largest_indicies.clear();
        row.largest_indicies.push_back(first_index);
      }
    } //else if size is 1 then we already have largest single index
  }

}

void get_col_data(int r, int c, unordered_map<int, Vector> &rows, unordered_map<int, Vector> &cols, int * matrix) {
  int val = 0;
  int temp[MAX];
  for (int j = 0; j < c; j++) {
    int num_col_largest = 0;
    int largest = 0;
    for (int i = 0; i < r; i++) {
      val = matrix[i * c + j];
      if (val > largest) {
        largest = val;
        num_col_largest = 0;
        temp[num_col_largest] = i;
      }
      else if (val == largest) {
        temp[num_col_largest] = i;
      }
      num_col_largest++;
    }
    Vector col_obj(num_col_largest, largest, temp);
    rows[j] = col_obj;
  }
}

void get_row_data(int r, int c, unordered_map<int, Vector> &rows, unordered_map<int, Vector> &cols, int * matrix) {

  int val = 0;
  int temp[MAX];
  for (int i = 0; i < r; i++) {
    int num_row_largest = 0;
    int largest = 0;
    for (int j = 0; j < c; j++) {
      val = matrix[i * c + j];
      Vector col_obj = cols[j];
      if (val > largest) {
        largest = val;
        num_row_largest = 0;
        temp[num_row_largest] = i;
      }
      else if (val == largest) {
        temp[num_row_largest] = i;
      }
      num_row_largest++;
    }
    Vector row_obj(num_row_largest, largest, temp);
    rows[i] = row_obj;
  }
}

void parse_input(int r, int c, int *matrix) {
  int val = 0;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cin >> val;
      matrix[i * c + j] = val;
    }
  }
}

int main() {
  int r, c;
  cin >> r;
  cin >> c;
  unordered_map<int, Vector> rows;
  unordered_map<int, Vector> cols;
  int *matrix = (int *)malloc(sizeof(int *) * r * c);
  parse_input(r, c, matrix);
  get_row_data(r, c, rows, cols, matrix);
  get_col_data(r, c, rows, cols, matrix);
  compute_row_largest(rows, cols, matrix, r, c);
  compute_col_largest(rows, cols, matrix, r, c);
  cout << compute_sum(rows, cols, matrix, r, c) << endl;
}



