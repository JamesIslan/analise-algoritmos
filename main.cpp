#include "algoritmos/algorithms.h"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

void medirTempoExecucao() {
  int n = 10000;
  int chave = -1;

  // Medindo Busca Sequencial
  auto start = high_resolution_clock::now();
  buscaSequencial(n, chave);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  cout << "Tempo Busca Sequencial: " << duration.count() << " ms" << endl;

  // Medindo Busca Binaria
  start = high_resolution_clock::now();
  buscaBinaria(n, chave);
  stop = high_resolution_clock::now();
  duration = duration_cast<milliseconds>(stop - start);
  cout << "Tempo Busca Binaria: " << duration.count() << " ms" << endl;

  // Medindo Selection Sort
  start = high_resolution_clock::now();
  selectionSort(n);
  stop = high_resolution_clock::now();
  duration = duration_cast<milliseconds>(stop - start);
  cout << "Tempo Selection Sort: " << duration.count() << " ms" << endl;

  // Medindo Insertion Sort
  start = high_resolution_clock::now();
  insertionSort(n);
  stop = high_resolution_clock::now();
  duration = duration_cast<milliseconds>(stop - start);
  cout << "Tempo Insertion Sort: " << duration.count() << " ms" << endl;
}

int main() {
  cout << "Iniciando medicao de tempo dos algoritmos..." << endl;
  medirTempoExecucao();
  return 0;
}
