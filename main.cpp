#include "algoritmos/algorithms.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>

using namespace std;
using namespace std::chrono;

// Função auxiliar para criar os arquivos CSV
void exportarParaCSV(string nomeArquivo,
                     const vector<tuple<int, double>> &dados) {
  ofstream arquivo(nomeArquivo);

  if (arquivo.is_open()) {
    arquivo << "n,tempo_ms\n";
    for (const auto &t : dados) {
      arquivo << get<0>(t) << "," << fixed << setprecision(6) << get<1>(t)
              << "\n";
    }
    arquivo.close();
    cout << "Arquivo '" << nomeArquivo << "' gerado com sucesso!" << endl;
  } else {
    cerr << "Erro ao abrir o arquivo " << nomeArquivo << " para escrita."
         << endl;
  }
}

void medirTempoExecucao() {
  vector<tuple<int, double>> resBuscaSequencial, resBuscaBinaria,
      resSelectionSort, resInsertionSort;
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1, 1000000);

  int chave = -1;

  for (int n = 10; n <= 20000; n += 100) {
    cout << "Testando n = " << n << "..." << endl;

    vector<int> arrBase(n);
    for (int i = 0; i < n; i++)
      arrBase[i] = dis(gen);

    // BUSCA SEQUENCIAL
    auto start = high_resolution_clock::now();
    // buscaSequencial(arrBase, chave);
    auto stop = high_resolution_clock::now();
    // // Usando duration com double em milissegundos nativamente
    // duration<double, std::milli> tempoSeq = stop - start;
    // resBuscaSequencial.push_back(make_tuple(n, tempoSeq.count()));

    // BUSCA BINÁRIA
    // vector<int> arrOrdenado = arrBase;
    // sort(arrOrdenado.begin(), arrOrdenado.end());
    // start = high_resolution_clock::now();
    // buscaBinaria(arrOrdenado, chave);
    // stop = high_resolution_clock::now();
    // duration<double, std::milli> tempoBin = stop - start;
    // resBuscaBinaria.push_back(make_tuple(n, tempoBin.count()));

    // SELECTION SORT
    // vector<int> arrSel = arrBase;
    // start = high_resolution_clock::now();
    // selectionSort(arrSel);
    // stop = high_resolution_clock::now();
    // duration<double, std::milli> tempoSel = stop - start;
    // resSelectionSort.push_back(make_tuple(n, tempoSel.count()));

    // INSERTION SORT
    vector<int> arrIns = arrBase;
    start = high_resolution_clock::now();
    insertionSort(arrIns);
    stop = high_resolution_clock::now();
    duration<double, std::milli> tempoIns = stop - start;
    resInsertionSort.push_back(make_tuple(n, tempoIns.count()));
  }

  // Exportando cada vetor para seu respectivo arquivo CSV
  cout << "\nExportando resultados..." << endl;
  // exportarParaCSV("busca_sequencial.csv", resBuscaSequencial);
  // exportarParaCSV("busca_binaria.csv", resBuscaBinaria);
  // exportarParaCSV("selection_sort.csv", resSelectionSort);
  exportarParaCSV("insertion_sort.csv", resInsertionSort);
}

int main() {
  cout << "Iniciando medicao de tempo dos algoritmos..." << endl;
  medirTempoExecucao();
  return 0;
}
