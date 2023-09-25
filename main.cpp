#include "classes.h"

using namespace std;

//numero de vertices, numero de arestas, grau minimo, grau maximo, grau medio, e mediana do grau
//representar grafo com uma matriz de adjacencia e vetor de adjacencia
//BFS, DFS, árvore geradora com níveis
//calcular distância entre vértices (BFS) e diâmetro
//Número de componentes conexas, tamanho (qtde de vértices) e lista de vértices da componente (por ordem de tamanho)

//Quantidade de memória usada pela matriz x vetor de adj
//verificar tempo médio- 100 BFS e DFS (sem considerar tempo de leitura e escrita)
//pai dos vertices 10, 20, 30 pela BFS e DFS iniciando por 1,2,3
//distância entre os vértices (10,20), (10,30), (20,30)
//quantas componentes conexas, qual o tamanho da maior e menor componente
//diametro por algoritmo aproximativo
 
int main()
{
    grafo grafo;

    int n, v1, v2;

    ifstream arquivo("teste.txt");
    
    arquivo >> n;
    grafo.num_vertices = n; 

    vector<vector<int>> matriz_adj(n, vector<int>(n, 0));
    vector<int> grau_vertices(n, 0);
    vector<vector<int>> vetor_adj(n);
    
    while (arquivo >> v1 >> v2) {
        //Incrementando grau do vertice ao ler uma aresta que ele pertence
        cout<< v1 << " ";
        cout<< v2 <<endl;

        grau_vertices[v1 -1]++;
        grau_vertices[v2 -1]++;

        grafo.num_arestas ++;

        matriz_adj[v1-1][v2-1] = 1;
        matriz_adj[v2-1][v1-1] = 1;

        vetor_adj[v1-1].push_back(v2-1);
        vetor_adj[v2-1].push_back(v1-1);
    }

    cout<< "num arestas " << grafo.num_arestas << endl;
    
    for (int i = 0; i < grau_vertices.size(); i++)
        cout << grau_vertices[i] << " "; 


    // Imprime a matriz
    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << vetor_adj[i][j] << "\t"; // \t para espaçamento entre elementos
        }
        cout << endl; // Nova linha após cada linha da matriz
    }


    return 0;
}
