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

void preencherVetor(vector<int> &vetor, int numValores) {
  // GERAÇÃO DE SEED RANDOMICA
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1, 1000000);

  // PREENCHIMENTO DE VETOR
  for (int i = 0; i < numValores; i++)
    vetor[i] = dis(gen);
};

// Criação de template para executar algoritmo genérico
// template <typename Algoritmo>
// void executarBusca(Algoritmo algoritmo, string tipoBusca) {
//   int chave = -1; // Chave não existente para forçar pior caso
//   cout << "Executando " << tipoBusca << " ..." << endl;
//   algoritmo();
//   std::cout << "Finalizada." << std::endl;
// }

void rodarBuscaSequencial(vector<tuple<int, double>> &tuplaValores, int maxItens) {
  int chave = -1; // Chave não existente para forçar pior caso

  cout << "Executando busca sequencial..." << endl;
  for (int n = 10; n <= maxItens; n += 100) {
    vector<int> vetor(n);
    preencherVetor(vetor, n);
    cout << "Testando n = " << n << "..." << endl;

    // MEDIÇÃO DO TEMPO
    auto start = high_resolution_clock::now();
    buscaSequencial(vetor, chave);
    auto stop = high_resolution_clock::now();
    duration<double, std::milli> tempoSeq = stop - start;

    // ADIÇÃO DO PAR (N, TEMPO)
    tuplaValores.push_back(make_tuple(n, tempoSeq.count()));
  }
};

void rodarBuscaBinaria(vector<tuple<int, double>> &tuplaValores, int maxItens) {
  int chave = -1; // Chave não existente para forçar pior caso

  cout << "Executando busca binária..." << endl;
  for (int n = 10; n <= maxItens; n += 100) {
    vector<int> vetor(n);
    preencherVetor(vetor, n);
    cout << "Testando n = " << n << "..." << endl;

    // MEDIÇÃO DO TEMPO
    auto start = high_resolution_clock::now();
    buscaBinaria(vetor, chave);
    auto stop = high_resolution_clock::now();
    duration<double, std::milli> tempoSeq = stop - start;

    // ADIÇÃO DO PAR (N, TEMPO)
    tuplaValores.push_back(make_tuple(n, tempoSeq.count()));
  }
}

void rodarSelectionSort(vector<tuple<int, double>> &tuplaValores, int maxItens) {
  cout << "Executando selection sort..." << endl;
  for (int n = 10; n <= maxItens; n += 1000) {
    vector<int> vetor(n);
    preencherVetor(vetor, n);
    cout << "Testando n = " << n << "..." << endl;

    // MEDIÇÃO DO TEMPO
    auto start = high_resolution_clock::now();
    selectionSort(vetor);
    auto stop = high_resolution_clock::now();
    duration<double, std::milli> tempoSeq = stop - start;

    // ADIÇÃO DO PAR (N, TEMPO)
    tuplaValores.push_back(make_tuple(n, tempoSeq.count()));
  }
};
void rodarInsertionSort(vector<tuple<int, double>> &tuplaValores, int maxItens) {
  cout << "Executando insertion sort..." << endl;
  for (int n = 10; n <= maxItens; n += 1000) {
    vector<int> vetor(n);
    preencherVetor(vetor, n);
    cout << "Testando n = " << n << "..." << endl;

    // MEDIÇÃO DO TEMPO
    auto start = high_resolution_clock::now();
    selectionSort(vetor);
    auto stop = high_resolution_clock::now();
    duration<double, std::milli> tempoSeq = stop - start;

    // ADIÇÃO DO PAR (N, TEMPO)
    tuplaValores.push_back(make_tuple(n, tempoSeq.count()));
  }
};

int main() {
  cout << "Iniciando medicao de tempo dos algoritmos..." << endl;
  vector<tuple<int, double>> resBuscaSequencial, resBuscaBinaria, resSelectionSort, resInsertionSort;

  // BUSCA SEQUENCIAL
  rodarBuscaSequencial(resBuscaSequencial, 100000);
  exportarParaCSV("busca_sequencial.csv", resBuscaSequencial);

  // BUSCA BINÁRIA
  rodarBuscaBinaria(resBuscaBinaria, 100000);
  exportarParaCSV("busca_binaria.csv", resBuscaBinaria);

  // SELECTION SORRT
  rodarSelectionSort(resSelectionSort, 50000);
  exportarParaCSV("selection_sort.csv", resSelectionSort);

  // INSERTION SORRT
  rodarInsertionSort(resInsertionSort, 50000);
  exportarParaCSV("insertion_sort.csv", resInsertionSort);
  return 0;
}
