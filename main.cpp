#include "biblioteca.h"
#include <ctime>
#include <stdlib.h>

using namespace std;

void mostrarMenu1() {
  cout << "Escolha a operacao desejada:\n\n"
       << endl
       << "1 - Busca em largura \n"
       << endl
       << "2 - Busca em profundidade\n"
       << endl
       << "3 - Distâncias.\n"
       << endl
       << "4 - Diâmetro.\n"
       << endl
       << "5 - Componentes conexos.\n"
       << endl
       << "6 - Sair.\n"
       << endl;
}

void mostrarMenu2() {
  cout << "Escolha a operacao desejada:\n\n"
       << endl
       << "1 - Distância e caminho mínimo usando Djikstra com Heap \n"
       << endl
       << "2 - Distância e caminho mínimo usando Djikstra sem Heap\n"
       << endl
       << "3 - Sair.\n"
       << endl;

}

int main() {

  int escolha;
  string arq_texto;

  cout << "Insira o nome do arquivo texto a ser lido: ";
  cin >> arq_texto;
  cin.ignore(100, '\n');

  if (arq_texto.substr(arq_texto.size() - 4) != ".txt") {
    cout << "O nome do arquivo nao continha '.txt', adicionado." << endl;
    arq_texto = arq_texto + ".txt";
  }
  
  cout << "Voce deseja trabalhar com grafos com ou sem pesos? \n 1 -" " Com pesos \n 2 - Sem pesos \n 3 - Grafo direcionado"<< endl;
  cin >> escolha;


  if (escolha == 1){

    int resultado = 0;
    int numero_vertice_inicial = 1;
    int numero_vertice_final = 2;
    int opcao_djikstra;
    string caminho;

    grafo grafo(arq_texto, escolha);

    do {
    mostrarMenu2();

    cin >> opcao_djikstra;
    cin.ignore(50, '\n');

    vector<float> distancias;
    vector<int> pais;
      
    switch (opcao_djikstra) {

    case 1:
      cout << "Insira o numero do vertice a ser utilizado como inicial: ";
      cin >> numero_vertice_inicial;
      cin.ignore(50, '\n');

        cout << "Insira o numero do vertice a ser utilizado como final: ";
        cin >> numero_vertice_final;
        cin.ignore(50, '\n');
      
        resultado = grafo.Dijkstra_Heap(numero_vertice_inicial, pais, distancias);

      cout << endl;

      if (resultado == 0){
        caminho = grafo.Caminho_Min(numero_vertice_final, pais);
        cout << "Caminho: " << caminho << endl;      
        cout << "Distância: " << distancias[numero_vertice_final - 1] << endl;
        cout << endl;
      }

      else{
      cout << "Ainda não foi implementado o cálculo de distâncias mínimas com pesos negativos." << endl;
      cout << "Finalizando o programa..." <<endl;}

      break;
      

    case 2:
      cout << "Insira o numero do vertice a ser utilizado como inicial: ";
      cin >> numero_vertice_inicial;
      cin.ignore(50, '\n');

        cout << "Insira o numero do vertice a ser utilizado como final: ";
        cin >> numero_vertice_final;
        cin.ignore(50, '\n');
      
        resultado = grafo.Dijkstra(numero_vertice_inicial, pais, distancias);

        cout << endl;

        if (resultado == 0){
          caminho = grafo.Caminho_Min(numero_vertice_final, pais);
          cout << "Caminho: " << caminho << endl;      
          cout << "Distância: " << distancias[numero_vertice_final - 1] << endl;
          cout << endl;
        }

          else{
          cout << "Ainda não foi implementado o cálculo de distâncias mínimas com pesos negativos." << endl;
          cout << "Finalizando o programa..." <<endl;}

          break;

    case 3:
          break;

    default:
      cout << "Por favor, selecione uma dentre as opcoes validas!" << endl;
      break;
    
    }
  } while (opcao_djikstra != 3);

  }
    
  else if (escolha == 2) {
    
    int n, numero_vertice, numero_vertice2, opcao;
    cout << "Voce deseja trabalhar com matriz ou vetor de adjacência? \n 1 -"
      "Matriz \n 2 - Vetor"
    << endl;
    cin >> escolha;
    escolha += 2;
    
    do {

      grafo grafo(arq_texto, escolha);
      n = grafo.num_vertices;
  
      grafo.Calculo_Graus();
  
      mostrarMenu1();
      vector<int> pai(n, 0);
      vector<int> nivel(n, 0);
      vector<int> explorados(n, 0);
  
      cin >> opcao;
      cin.ignore(50, '\n');
  
      switch (opcao) {
  
      case 1:
        cout << "Insira o numero do vertice a ser utilizado como inicial: ";
        cin >> numero_vertice;
  
        grafo.BFS(numero_vertice, pai, nivel, explorados);
  
        break;
  
      case 2:
        cout << "Insira o numero do vertice a ser utilizado como inicial: ";
        cin >> numero_vertice;
  
        grafo.DFS(numero_vertice, pai, nivel, explorados);
        break;
  
      case 3:
        cout << "Insira o numero do vertice 1: ";
        cin >> numero_vertice;
        cout << "Insira o numero do vertice 2: ";
        cin >> numero_vertice2;
        cout << grafo.Distancia(numero_vertice, numero_vertice2, pai) << endl;
        break;
  
      case 4:
        cout << grafo.Diametro() << endl;
        break;
  
      case 5:
        grafo.Componente_Conexa();
        break;
  
      case 6:
        break;
  
      default:
        cout << "Por favor, selecione uma dentre as opcoes validas!" << endl;
        break;
      }
  
    } while (opcao != 6);
  }

  else if(escolha == 3) {
    int numero_vertice, numero_vertice2, usar_arquivo=0; 
    
    escolha = 5;

    cout << "Insira o numero do vertice a ser utilizado como inicial: ";
    cin >> numero_vertice;
    cin.ignore(50, '\n');

      cout << "Insira o numero do vertice a ser utilizado como final: ";
      cin >> numero_vertice2;
      cin.ignore(50, '\n');
    
    cout << "Deseja salvar o fluxo nas arestas em disco? \n" << "1- Sim \n" << "2- Nao" <<endl;
    
    cin >> usar_arquivo;
    cin.ignore(50, '\n');
    
    
    grafo grafo(arq_texto, escolha);

    int fluxo_maximo = 0;
    
    fluxo_maximo = grafo.Ford_Fulkerson(numero_vertice, numero_vertice2, usar_arquivo); 
    cout << "O fluxo maximo é: " << fluxo_maximo << endl;
  }
  return 0;
}


