#include <algorithm>
#include <cfloat>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class grafo {

public:
  grafo(string, int);
  int num_vertices = 0;
  int num_arestas = 0;
  int peso_negativo = 0;
  int escolha = 0; // indica se o usuário quer trabalhar com vetor ou matriz

  vector<vector<int>> matriz_adj;
  vector<vector<int>> vetor_adj;
  vector<vector<pair<int, float>>> vetor_adj_peso;
  vector<int> grau_vertices;
  vector<float> pesos;

  int BFS(int, vector<int> &, vector<int> &, vector<int> &);
  int DFS(int, vector<int> &, vector<int> &, vector<int> &);
  int Dijkstra(int, vector<int> &, vector<float> &);
  int Dijkstra_Heap(int, vector<int> &, vector<float> &);
  string Caminho_Min(int, vector<int> &);

  void Constroi_Grafo(ifstream &);

  void Calculo_Graus();
  int Diametro();
  int Distancia(int v1, int v2);
  int Componente_Conexa();
};
