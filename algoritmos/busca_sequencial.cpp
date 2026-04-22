#include "algorithms.h"
#include <vector>

void buscaSequencial(const std::vector<int> &arr, int chave) {
  int n = arr.size();
  for (int i = 0; i < n; i++) {
    if (arr[i] == chave) {
      return;
    }
  }
}
