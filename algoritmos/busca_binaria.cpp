#include "algorithms.h"
#include <vector>

void buscaBinaria(int n, int chave) {
  std::vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    arr[i] = i;
  }

  int esq = 0;
  int dir = n - 1;

  while (esq <= dir) {
    int meio = esq + (dir - esq) / 2;

    if (arr[meio] == chave)
      return;

    if (arr[meio] < chave)
      esq = meio + 1;
    else
      dir = meio - 1;
  }
}
