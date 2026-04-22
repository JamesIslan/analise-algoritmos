#include "algorithms.h"
#include <vector>

void buscaBinaria(const std::vector<int> &arr, int chave) {
  int n = arr.size();
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
