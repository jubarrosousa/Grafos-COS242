#include "biblioteca.h"

  grafo::grafo(string arquivo, int opcao) {

  escolha = opcao;
  
  ifstream file(arquivo);
    
  file >> num_vertices;
  grau_vertices.resize(num_vertices);
  int v1, v2;

  if(escolha ==1){
    matriz_adj.resize(num_vertices, vector<int>(num_vertices));
  }
    
  else{
      vetor_adj.resize(num_vertices);
  }

  while (file >> v1 >> v2) {
    // Incrementando grau do vertice ao ler uma aresta que ele pertence

    grau_vertices[v1 - 1]++;
    grau_vertices[v2 - 1]++;

    num_arestas++;
    
    if (escolha ==1)
    {
      matriz_adj[v1 - 1][v2 - 1] = 1;
      matriz_adj[v2 - 1][v1 - 1] = 1;
    }
    else
    {
      // Eh posicao em vetor de adjacencia mas eh o numero do vertice na lista
      vetor_adj[v1 - 1].push_back(v2);
      vetor_adj[v2 - 1].push_back(v1);
    }
    
  }
   
}

void grafo::Calculo_Graus() {

  sort(grau_vertices.begin(), grau_vertices.end());

  int grau_mediana = 0, grau_medio=0, grau_min=0, grau_max=0;

  // grau medio
  grau_medio = 2*num_arestas/num_vertices;
  // maior grau
  grau_max=grau_vertices[num_vertices - 1];
  // menor grau
  grau_min=grau_vertices[0];

  // mediana do grau
  if (num_vertices % 2 == 0) {
    int meio1 = num_vertices / 2 - 1;
    int meio2 = num_vertices / 2;
    grau_mediana=grau_vertices[meio1] +
                               grau_vertices[meio2] / 2.0;

  } else {
    int meio = num_vertices / 2;
    grau_mediana=grau_vertices[meio];
  }

  ofstream outputFile("output.txt");
  if (outputFile.is_open()) {
        outputFile << "Numero de vertices: "<<num_vertices<< endl;
        outputFile << "Numero de arestas: "<<num_arestas<< endl;
        outputFile << "Media do grau: "<<grau_medio<< endl;
        outputFile << "Mediana do grau: "<<grau_mediana<< endl;
        outputFile << "Grau minimo: "<<grau_min<< endl;
        outputFile << "Grau maximo: "<<grau_max<< endl;

        outputFile.close();
  }
}

int grafo::BFS(int s, vector<int> &pai, vector<int> &nivel,
                      vector<int> &explorados) {

  // 0 como marcacao para vertices nao explorados
  queue<int> fila;

  int v, u;

  pai[s - 1] = -1;
  explorados[s - 1] = 1;

  fila.push(s);

  while (fila.size() > 0) {
    
    v = fila.front();
    
    fila.pop();

    if(escolha ==1)
    {
      for (int i = 0; i < num_vertices; i++) 
      {
        u = matriz_adj[v - 1][i];
     
        if ((explorados[i] != 1) && (u==1)) 
        {
          explorados[i] = 1;
          fila.push(i+1);
          pai[i] = v;
          nivel[i] = nivel[v - 1] + 1;
        }
      }
    }
    
    else
    {
      for (unsigned int i = 0; i < vetor_adj[v - 1].size(); i++) 
      {
        u = vetor_adj[v - 1][i];
      
        if (explorados[u - 1] != 1) 
        {
          explorados[u - 1] = 1;
          fila.push(u);
          pai[u - 1] = v;
          nivel[u - 1] = nivel[v - 1] + 1;
        }
      }
    }

  }
  
  ofstream outputFile("bfs.txt");
  if (outputFile.is_open()) {
    for (int i = 0; i< num_vertices; i++){
      outputFile << i+1 << " "<< pai[i]<< " "<< nivel[i]<<endl;
    }
        
        outputFile.close();
}
  
  return 0;
  
}

int grafo::DFS(int s, vector<int> &pai, vector<int> &nivel,
                      vector<int> &explorados) {

  stack<int> pilha;

  int v, u;
  pai[s - 1] = -1;
  explorados[s - 1] = 1;
  pilha.push(s);

  while (pilha.size() > 0) {
    v = pilha.top();
    pilha.pop();

    if (escolha==1){
    for (int i = 0; i < num_vertices; i++) {
      u = matriz_adj[v - 1][i];

      if ((explorados[i] != 1) && (u==1)) {
        explorados[i] = 1;
        pilha.push(i+1);
        pai[i] = v;
        nivel[i] = nivel[v - 1] + 1;
        
      }
    }
    }
    else{
    for (unsigned int i = 0; i < vetor_adj[v - 1].size(); i++) {
      u = vetor_adj[v - 1][i];

      if (explorados[u - 1] != 1) {
        explorados[u - 1] = 1;
        pilha.push(u);
        pai[u - 1] = v;
        nivel[u - 1] = nivel[v - 1] + 1;
        
      }
    }
  }
  }
   
  ofstream outputFile("dfs.txt");
  if (outputFile.is_open()) {
    for (int i = 0; i< num_vertices; i++){
      outputFile << i+1 << " "<< pai[i]<< " "<< nivel[i]<<endl;
    }
        
        outputFile.close();
}

  return 0;
}

int grafo::Componente_Conexa(){

  vector<int> pais(num_vertices, 0);
  vector<int> niveis(num_vertices, 0);
  int vertice_inicial = 1;
  bool grafo_completo = false;
  vector<int> componentes_explorados(num_vertices, 0);
  vector <int> resultado;
  vector<pair<int,string>> componentes;

  
  while (grafo_completo == false) {
   
    int tamanho_componente=0;
    string str_componente;  
    
    BFS(vertice_inicial, pais, niveis, componentes_explorados);
    
    grafo_completo = true;
    for (size_t i = 0; i < componentes_explorados.size(); i++) {
      if (componentes_explorados[i] == 1) {
        tamanho_componente += 1;
        str_componente += " ";
        str_componente += to_string(i+1);
        componentes_explorados[i] = componentes_explorados[i] + 1;
      }

      else if (componentes_explorados[i] == 0) {
        // Precisa rodar mais uma BFS para o componente i
        vertice_inicial = i + 1;
        grafo_completo = false;
      }

      // Armazenar os indices em algum lugar pois eles formam uma componente
      // conexa e seu tamanho é o tamanho da componente
    }
    componentes.push_back(make_pair(tamanho_componente, str_componente));
  
  sort(componentes.rbegin(), componentes.rend()); 
 
}

  return 0;
}

int grafo::Diametro(){
  
  int diametro = -1, limite_bfs, inicio;
  
  if (num_vertices < 5000)
    limite_bfs = num_vertices;

  else
    limite_bfs = 5000;

  
  for (int i = 1; i <= limite_bfs; i++) {
    vector<int> nivel_diametro(num_vertices, 0);
    vector<int> pai_diametro(num_vertices, 0);
    vector<int> explorados_diametro(num_vertices, 0);
    if (num_vertices > 5000)
      inicio = rand() % num_vertices;

    else
      inicio = i;
    
    BFS(inicio, pai_diametro, nivel_diametro, explorados_diametro);
    
    for (int cont = 0; cont < limite_bfs; cont++) {
      if (nivel_diametro[cont] > diametro) {
        diametro = nivel_diametro[cont];
      }}

  }
  return diametro; 
}

int grafo::Distancia(int v1, int v2){
  vector<int> nivel(num_vertices, 0);
  vector<int> pai(num_vertices, 0);
  vector<int> explorados(num_vertices, 0);
  
  
  BFS(v1, pai, nivel, explorados);
    

  if (explorados[v2-1]==1)
    return (nivel[v2-1]);
  
  else
    return -1;

  
}
