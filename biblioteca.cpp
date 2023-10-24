#include "biblioteca.h"

grafo::grafo(string arquivo, int opcao) {

  escolha = opcao;

  ifstream file(arquivo);

  file >> num_vertices;
  grau_vertices.resize(num_vertices);
  int v1, v2;
  float peso;

  if (escolha == 1 || escolha == 2) {
    vetor_adj_peso.resize(num_vertices);
  }

  if (escolha == 3) {
    matriz_adj.resize(num_vertices, vector<int>(num_vertices));
  }
  if (escolha == 4) {
    vetor_adj.resize(num_vertices);
  }

  while (file >> v1 >> v2 >> peso) {
    // Incrementando grau do vertice ao ler uma aresta que ele pertence
    grau_vertices[v1 - 1]++;
    grau_vertices[v2 - 1]++;

    num_arestas++;

    pesos.push_back(peso);

    if (escolha == 1 || escolha == 2) {

      if (peso < 0)
        peso_negativo = 1;

      vetor_adj_peso[v1 - 1].push_back(make_pair(v2, peso));
      vetor_adj_peso[v2 - 1].push_back(make_pair(v1, peso));
    }
    if (escolha == 3) {
      matriz_adj[v1 - 1][v2 - 1] = 1;
      matriz_adj[v2 - 1][v1 - 1] = 1;
    }
    if (escolha == 4) {
      // Eh posicao em vetor de adjacencia mas eh o numero do vertice na lista
      vetor_adj[v1 - 1].push_back(v2);
      vetor_adj[v2 - 1].push_back(v1);
    
    }
   
  }
  
}

int grafo::Dijkstra_Heap(int s, vector<int> &pai, vector<float> &dist) {
  if (peso_negativo == 0) {

    dist.resize(num_vertices, FLT_MAX);
    pai.resize(num_vertices, -1);
    vector<bool> S(num_vertices, false);
    s--;
    dist[s] = 0;

    // Fila de prioridade que guarda <peso, pai >
    priority_queue<pair<float, int>, vector<pair<float, int>>,
                   greater<pair<float, int>>>
        heap;
    // Adicionando vertice inicial na fila com seu respectivo peso
    heap.push(make_pair(0, s+1));

    while (!heap.empty()) {
      int u = heap.top().second;
      heap.pop();
      u--;

      if (S[u])
        continue; // Para a iteracao para vertices ja explorados

      S[u] = true;

      for (unsigned int i = 0; i < vetor_adj_peso[u].size(); i++) {
        int v = vetor_adj_peso[u][i].first;
        float peso = vetor_adj_peso[u][i].second;
        v--;

        if (!S[v]) {
          if (dist[u] + peso < dist[v]) {
            dist[v] = dist[u] + peso;
            heap.push(make_pair(dist[v], v+1));
            pai[v] = u+1;
          }
        }
      }
    }
  }

  else {
    return 1;
  }

  return 0;
}

int grafo::Dijkstra(int s, vector<int> &pai, vector<float> &dist) {

  if (peso_negativo == 0) {
    dist.resize(num_vertices, -1);
    pai.resize(num_vertices, -1);
    vector<bool> Explorados(num_vertices, false);
    vector<int> S;
    int u = s;
    u--;
    dist[u] = 0;

    while (S.size() != num_vertices) {
      int max_dist = INT_MAX;
      for (int i = 0; i < num_vertices; i++) {
        if (dist[i] != -1 && dist[i] < max_dist && Explorados[i] == false) {
          u = i;
          max_dist = dist[i];
        }
      }

      Explorados[u] = true;
      S.push_back(u + 1);
      for (int i = 0; i < vetor_adj_peso[u].size(); i++) {
        int v = vetor_adj_peso[u][i].first;
        float peso = vetor_adj_peso[u][i].second;
        if (dist[v - 1] > dist[u] + peso || dist[v - 1] == -1) {
          dist[v - 1] = dist[u] + peso;
          pai[v - 1] = u + 1;
        }
      }
    }

    return 0;

  } else
    return 1;
}

string grafo::Caminho_Min(int s, vector<int> &pai) {
  string caminho = "";
  int aux;

  caminho += to_string(s);
  aux = s;

  aux--;

  while (pai[aux] != -1) {
    caminho += " ";
    caminho += to_string(pai[aux]);
    aux = pai[aux];
    aux--; // Indice no vetor eh o pai -1
  }

  return caminho;
}

void grafo::Calculo_Graus() {

  sort(grau_vertices.begin(), grau_vertices.end());

  int grau_mediana = 0, grau_medio = 0, grau_min = 0, grau_max = 0;

  // grau medio
  grau_medio = 2 * num_arestas / num_vertices;
  // maior grau
  grau_max = grau_vertices[num_vertices - 1];
  // menor grau
  grau_min = grau_vertices[0];

  // mediana do grau
  if (num_vertices % 2 == 0) {
    int meio1 = num_vertices / 2 - 1;
    int meio2 = num_vertices / 2;
    grau_mediana = grau_vertices[meio1] + grau_vertices[meio2] / 2.0;

  } else {
    int meio = num_vertices / 2;
    grau_mediana = grau_vertices[meio];
  }

  ofstream outputFile("output.txt");
  if (outputFile.is_open()) {
    outputFile << "Numero de vertices: " << num_vertices << endl;
    outputFile << "Numero de arestas: " << num_arestas << endl;
    outputFile << "Media do grau: " << grau_medio << endl;
    outputFile << "Mediana do grau: " << grau_mediana << endl;
    outputFile << "Grau minimo: " << grau_min << endl;
    outputFile << "Grau maximo: " << grau_max << endl;

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

    if (escolha == 3) {
      for (int i = 0; i < num_vertices; i++) {
        u = matriz_adj[v - 1][i];

        if ((explorados[i] != 1) && (u == 1)) {
          explorados[i] = 1;
          fila.push(i + 1);
          pai[i] = v;
          nivel[i] = nivel[v - 1] + 1;
        }
      }
    }

    else {
      for (unsigned int i = 0; i < vetor_adj[v - 1].size(); i++) {
        u = vetor_adj[v - 1][i];

        if (explorados[u - 1] != 1) {
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
    for (int i = 0; i < num_vertices; i++) {
      outputFile << i + 1 << " " << pai[i] << " " << nivel[i] << endl;
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

    if (escolha == 3) {
      for (int i = 0; i < num_vertices; i++) {
        u = matriz_adj[v - 1][i];

        if ((explorados[i] != 1) && (u == 1)) {
          explorados[i] = 1;
          pilha.push(i + 1);
          pai[i] = v;
          nivel[i] = nivel[v - 1] + 1;
        }
      }
    } else {
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
    for (int i = 0; i < num_vertices; i++) {
      outputFile << i + 1 << " " << pai[i] << " " << nivel[i] << endl;
    }

    outputFile.close();
  }

  return 0;
}

int grafo::Componente_Conexa() {

  vector<int> pais(num_vertices, 0);
  vector<int> niveis(num_vertices, 0);
  int vertice_inicial = 1;
  bool grafo_completo = false;
  vector<int> componentes_explorados(num_vertices, 0);
  vector<int> resultado;
  vector<pair<int, string>> componentes;

  while (grafo_completo == false) {

    int tamanho_componente = 0;
    string str_componente;

    BFS(vertice_inicial, pais, niveis, componentes_explorados);

    grafo_completo = true;
    for (size_t i = 0; i < componentes_explorados.size(); i++) {
      if (componentes_explorados[i] == 1) {
        tamanho_componente += 1;
        str_componente += " ";
        str_componente += to_string(i + 1);
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

int grafo::Diametro() {

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
      }
    }
  }
  return diametro;
}

int grafo::Distancia(int v1, int v2) {
  vector<int> nivel(num_vertices, 0);
  vector<int> pai(num_vertices, 0);
  vector<int> explorados(num_vertices, 0);

  BFS(v1, pai, nivel, explorados);

  if (explorados[v2 - 1] == 1)
    return (nivel[v2 - 1]);

  else
    return -1;
}
