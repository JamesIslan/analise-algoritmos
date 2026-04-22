#include "algorithms.h"
#include <algorithm>
#include <cstdlib>
#include <vector>

void selectionSort(int n) {
  std::vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    arr[i] = rand() % n;
  }

  for (int i = 0; i < n - 1; i++) {
    int min_idx = i;
    for (int j = i + 1; j < n; j++) {
      if (arr[j] < arr[min_idx]) {
        min_idx = j;
      }
    }
    std::swap(arr[min_idx], arr[i]);
  }
}
