#include <iostream>
#include <vector>
int* tree;
int* arr;

int Min(int x, int y) { return x <= y ? x : y; }
int Max(int x, int y) { return x > y ? x : y; }
int Sum(int l_arr, int r_arr, int node_num, int left, int right) {
  int res = 0;
  if (left > right) {
    return 0;
  }
  if (left == l_arr && right == r_arr) {
    return tree[node_num];
  }
  int midd = (l_arr + r_arr) / 2;
  res += Sum(l_arr, midd, 2 * node_num, left, Min(right, midd));
  res += Sum(midd + 1, r_arr, 2 * node_num + 1, Max(left, midd + 1), right);
  return res;
}

void BuildTree(int node_num, int left, int right) {
  if (left == right) {
    tree[node_num] = arr[right];
  } else {
    int midd = (left + right) / 2;
    BuildTree(node_num * 2, left, midd);
    BuildTree(node_num * 2 + 1, midd + 1, right);
    tree[node_num] = tree[2 * node_num] + tree[2 * node_num + 1];
  }
}

void Change(int l_arr, int r_arr, int node_num, int ind, int val) {
  if (ind < l_arr || ind > r_arr) {
    return;
  }
  if (l_arr == r_arr && r_arr == ind) {
    if (ind % 2 == 0) {
      val *= -1;
    }
    tree[node_num] = val;
    arr[ind] = val;
  } else {
    int midd = (l_arr + r_arr) / 2;
    if (ind > midd) {
      Change(midd + 1, r_arr, 2 * node_num + 1, ind, val);
    } else {
      Change(l_arr, midd, 2 * node_num, ind, val);
    }
    tree[node_num] = tree[2 * node_num] + tree[2 * node_num + 1];
  }
}

int main() {
  int arr_length;
  std::cin >> arr_length;
  arr = new int[arr_length + 1];
  tree = new int[4 * (arr_length + 1)];
  int mult = 1;
  for (int i = 1; i <= arr_length; i++, mult *= -1) {
    std::cin >> arr[i];
    arr[i] *= mult;
  }
  BuildTree(1, 1, arr_length);

  int req_num;
  std::cin >> req_num;
  int flag;
  int res;
  int first, second;
  for (int k = 0; k < req_num; k++) {
    std::cin >> flag;
    std::cin >> first >> second;
    if (flag == 0) {
      Change(1, arr_length, 1, first, second);
    }
    if (flag == 1) {
      res = Sum(1, arr_length, 1, first, second);
      if (first % 2 == 0) {
        res *= -1;
      }
      std::cout << res << std::endl;
    }
  }
  std::cout << std::endl;
  delete[] arr;
  delete[] tree;
}