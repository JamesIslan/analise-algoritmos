#include "algorithms.h"
#include <cstdlib>
#include <vector>

void buscaSequencial(int n, int chave) {
  std::vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    arr[i] = rand() % n;
  }

  for (int i = 0; i < n; i++) {
    if (arr[i] == chave) {
      return;
    }
  }
}
