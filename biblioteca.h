include <algorithm>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class grafo {

public:

  grafo(string, int);
  int num_vertices=0;
  int num_arestas=0;
  int escolha = 0; //indica se o usuário quer trabalhar com vetor ou matriz

  vector<vector<int>> matriz_adj;
  vector<vector<int>> vetor_adj;
  vector<int> grau_vertices;

  int BFS(int, vector<int> &, vector<int> &, vector<int> &);
  int DFS(int, vector<int> &, vector<int> &, vector<int> &);

  void Constroi_Grafo(ifstream &);

  void Calculo_Graus();
  int Diametro();
  int Distancia(int v1, int v2);
  int Componente_Conexa();
};
