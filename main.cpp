#include "algoritmos/algorithms.h"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
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

// Preenchimento para ordenação (pior caso: decrescente)
void preencherVetorPiorCasoOrdenacao(vector<int> &vetor, int n) {
  for (int i = 0; i < n; i++) {
    vetor[i] = n - i;
  }
}

// Preenchimento para busca (vetor ordenado crescente)
void preencherVetorOrdenado(vector<int> &vetor, int n) {
  for (int i = 0; i < n; i++) {
    vetor[i] = i;
  }
}

void rodarBuscaSequencial(vector<tuple<int, double>> &tuplaValores,
                          int maxItens) {
  cout << "Executando Busca Sequencial..." << endl;
  for (int n = 10; n <= maxItens; n += 10000) {
    vector<int> vetor(n);
    preencherVetorOrdenado(vetor, n);
    cout << "Testando n = " << n << "..." << endl;

    auto start = high_resolution_clock::now();
    // Busca por um valor que não existe para forçar percorrer tudo
    buscaSequencial(vetor, -1);
    auto stop = high_resolution_clock::now();
    duration<double, std::milli> tempoSeq = stop - start;

    tuplaValores.push_back(make_tuple(n, tempoSeq.count()));
  }
}

void rodarBuscaBinaria(vector<tuple<int, double>> &tuplaValores, int maxItens) {
  cout << "Executando Busca Binária..." << endl;
  for (int n = 10; n <= maxItens; n += 10000) {
    vector<int> vetor(n);
    preencherVetorOrdenado(vetor, n);
    cout << "Testando n = " << n << "..." << endl;

    auto start = high_resolution_clock::now();
    buscaBinaria(vetor, -1);
    auto stop = high_resolution_clock::now();
    duration<double, std::milli> tempoSeq = stop - start;

    tuplaValores.push_back(make_tuple(n, tempoSeq.count()));
  }
}

void rodarSelectionSort(vector<tuple<int, double>> &tuplaValores,
                        int maxItens) {
  cout << "Executando Selection Sort..." << endl;
  for (int n = 10; n <= maxItens; n += 1000) {
    vector<int> vetor(n);
    preencherVetorPiorCasoOrdenacao(vetor, n);
    cout << "Testando n = " << n << "..." << endl;

    auto start = high_resolution_clock::now();
    selectionSort(vetor);
    auto stop = high_resolution_clock::now();
    duration<double, std::milli> tempoSeq = stop - start;

    tuplaValores.push_back(make_tuple(n, tempoSeq.count()));
  }
}

void rodarInsertionSort(vector<tuple<int, double>> &tuplaValores,
                        int maxItens) {
  cout << "Executando Insertion Sort..." << endl;
  for (int n = 10; n <= maxItens; n += 1000) {
    vector<int> vetor(n);
    preencherVetorPiorCasoOrdenacao(vetor, n);
    cout << "Testando n = " << n << "..." << endl;

    auto start = high_resolution_clock::now();
    insertionSort(vetor);
    auto stop = high_resolution_clock::now();
    duration<double, std::milli> tempoSeq = stop - start;

    tuplaValores.push_back(make_tuple(n, tempoSeq.count()));
  }
}

int main() {
  vector<tuple<int, double>> resBuscaSequencial, resBuscaBinaria,
      resSelectionSort, resInsertionSort;

  // BUSCAS

  rodarBuscaSequencial(resBuscaSequencial, 10000000);
  exportarParaCSV("amostras/busca_sequencial.csv", resBuscaSequencial);

  rodarBuscaBinaria(resBuscaBinaria, 10000000);
  exportarParaCSV("amostras/busca_binaria.csv", resBuscaBinaria);

  // ORDENAÇÃO

  rodarSelectionSort(resSelectionSort, 50000);
  exportarParaCSV("amostras/selection_sort.csv", resSelectionSort);

  rodarInsertionSort(resInsertionSort, 50000);
  exportarParaCSV("amostras/insertion_sort.csv", resInsertionSort);

  return 0;
}
