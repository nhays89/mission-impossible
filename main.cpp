#include <iostream>
#include <unordered_map>
#include <vector>
#include <stdlib.h>

typedef struct node {
  int count;
  int max;
  bool is;
} Node;

unsigned long long int total;
int r, c;
std::vector<int> mtrx, mtrx_exp;
static std::vector<std::pair<int, int>> stk;
std::unordered_map<int, Node> c_map;
std::unordered_map<int, Node> r_map;

bool rmv(const int i, const int j, int val, int r_cnt, int c_cnt, int r_max, int c_max) {
  bool r_is = r_map[i].is;
  bool c_is = c_map[j].is;
  bool ret;
  if (r_is && c_is || val < r_max && val < c_max) {
    ret = true;
  }
  else if ((r_is || val < r_max) && c_cnt > 1) {
    c_map[j].count--;
    ret = true;
  }
  else if ((c_is || val < c_max) && r_cnt > 1) {
    r_map[i].count--;
    ret = true;
  }
  return ret;
}
//#pragma optimize("", off)

void resolve(const int i, const int j, const int val, bool down) {

  int r_max = r_map[i].max;
  int c_max = c_map[j].max;
  int c_cnt = c_map[j].count;
  int r_cnt = r_map[i].count;

  if (rmv(i,j, val, r_cnt, c_cnt, r_max, c_max)) { 
    if (mtrx[i * c + j] > 0) total -= 1;
  }
  else if(val == r_max && r_cnt == 1) { 
    total -= val;
    r_map[i].is = true;
    if (val == c_max) c_map[j].is = true;
  }
  else if (val == c_max && c_cnt == 1) {
    total -= val;
    c_map[j].is = true;
    if (val == r_max) r_map[i].is = true;
  }
  else {
    if (down) {
      stk.push_back(std::make_pair(i, j));
    }
    else {
      total -= val;
      r_map[i].is = true;
      c_map[j].is = true;
    }
  }
}
#pragma optimize("", on)
void traverse_up() {
  while (!stk.empty()) {
    std::pair<int, int> p = stk.back();
    int i = p.first;
    int j = p.second;
    resolve(i, j, mtrx_exp[i * c + j], false);
    stk.pop_back();
  }
}


void traverse_down() {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      int val = mtrx_exp[i * c + j];
      resolve(i, j, val, true);
    }
  }
}

void process() {
  traverse_down();
  traverse_up(); 
}


void expand() {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      int val = mtrx[i * c + j];
      if (val > 0 && val < r_map[i].max && r_map[i].max == c_map[j].max) {
        mtrx_exp[i * c + j] = r_map[i].max;
        r_map[i].count++;
        c_map[j].count++;
      }
    }
  }
}


void fill() {
  int val;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      std::cin >> val;
      mtrx[i * c + j] = val;
      total += val;
      if (val > r_map[i].max) {
        r_map[i].max = val;
        r_map[i].count = 1;
      }
      else if (val == r_map[i].max) {
        r_map[i].count++;
      }
      if (val > c_map[j].max) {
        c_map[j].max = val;
        c_map[j].count = 1;
      }
      else if (val == c_map[j].max) {
        c_map[j].count++;
      }
    }
  }
}

int main() {

  while (std::cin >> r >> c) {
    total = 0;
    r_map.clear();
    c_map.clear();
    mtrx.resize(r * c);
    mtrx_exp.resize(r * c);
    stk.clear();
    fill();
    std::copy(mtrx.begin(), mtrx.end(), mtrx_exp.begin());
    expand();
    process();
    std::cout << total << std::endl;
  }
}
