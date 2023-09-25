#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class grafo{
     public:
        int num_vertices = 0;
        int num_arestas = 0;
        int grau_min = 0;
        int grau_max = 0;
        int grau_mediana = 0;

        //vector<vector<int>>matriz_adj(int num_vertices);
        vector<vector<int>>vetor_adj;

};
