#include "algoritmos/algorithms.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>

using namespace std;
using namespace std::chrono;

void medirTempoExecucao() {
  // Vetores de tuplas para guardar os resultados: (n, tempo)
  vector<tuple<int, double>> resBuscaSequencial, resBuscaBinaria, resSelectionSort, resInsertionSort;

  // Gerador de números randômicos
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1, 1000000);

  int chave = -1; // Chave não existente para representar o pior caso

  for (int n = 10; n <= 10000; n += 100) {
    cout << "Testando n = " << n << "..." << endl;

    // Preenchendo a lista com valores randômicos
    vector<int> arrBase(n);
    for (int i = 0; i < n; i++) {
      arrBase[i] = dis(gen);
    }

    // BUSCA SEQUENCIAL
    auto start = high_resolution_clock::now();
    buscaSequencial(arrBase, chave);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    resBuscaSequencial.push_back(make_tuple(n, duration.count() / 1000.0));

    // BUSCA BINÁRIA
    // A busca binária requer um array ordenado
    vector<int> arrOrdenado = arrBase;
    sort(arrOrdenado.begin(), arrOrdenado.end());
    start = high_resolution_clock::now();
    buscaBinaria(arrOrdenado, chave);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    resBuscaBinaria.push_back(make_tuple(n, duration.count() / 1000.0));

    // SELECTION SORT
    // Fazemos uma cópia para não alterar o vetor base original nos testes subsequentes
    vector<int> arrSel = arrBase;
    start = high_resolution_clock::now();
    selectionSort(arrSel);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    resSelectionSort.push_back(make_tuple(n, duration.count() / 1000.0));

    // INSERTION SORT
    vector<int> arrIns = arrBase;
    start = high_resolution_clock::now();
    insertionSort(arrIns);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    resInsertionSort.push_back(make_tuple(n, duration.count() / 1000.0));
  }

  // Imprimindo resultados
  cout << "\nResultados (N, Tempo em ms):" << endl;

  cout << "Busca Sequencial:" << endl;
  for (const auto &t : resBuscaSequencial) {
    cout << "(" << get<0>(t) << ", " << get<1>(t) << " ms) ";
  }
  cout << "\n";

  cout << "Busca Binaria:" << endl;
  for (const auto &t : resBuscaBinaria) {
    cout << "(" << get<0>(t) << ", " << get<1>(t) << " ms) ";
  }
  cout << "\n";

  cout << "Selection Sort:" << endl;
  for (const auto &t : resSelectionSort) {
    cout << "(" << get<0>(t) << ", " << get<1>(t) << " ms) ";
  }
  cout << "\n";

  cout << "Insertion Sort:" << endl;
  for (const auto &t : resInsertionSort) {
    cout << "(" << get<0>(t) << ", " << get<1>(t) << " ms) ";
  }
  cout << endl;
}

int main() {
  cout << "Iniciando medicao de tempo dos algoritmos..." << endl;
  medirTempoExecucao();
  return 0;
}
