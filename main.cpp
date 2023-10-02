#include "biblioteca.h"
#include <ctime>
#include <stdlib.h>

using namespace std;


void mostrarMenu () {
    cout << "Escolha a operacao desejada:\n\n" <<endl
    << "1 - Busca em largura \n" <<endl
    << "2 - Busca em profundidade\n" <<endl
    << "3 - Distâncias.\n" <<endl
    << "4 - Diâmetro.\n" <<endl
    << "5 - Componentes conexos.\n" <<endl
    << "6 - Sair.\n" <<endl;
}

 int main() {

   int n, numero_vertice, numero_vertice2, opcao, escolha;
   string arq_texto;
  
   cout << "Insira o nome do arquivo texto a ser lido: ";
   cin >> arq_texto;
   cin.ignore(100, '\n');
  
   if (arq_texto.substr(arq_texto.size() - 4) != ".txt") {
         cout << "O nome do arquivo não continha '.txt', adicionado."<<endl;
         arq_texto =  arq_texto + ".txt";
   }
  
   cout << "Voce deseja trabalhar com matriz ou vetor de adjacência? \n 1 - Matriz \n 2 - Vetor" <<endl;
   cin >> escolha;
  
   grafo grafo(arq_texto, escolha);
   n = grafo.num_vertices;

   grafo.Calculo_Graus();

       do {
         mostrarMenu();
           vector<int> pai(n, 0);
           vector<int> nivel(n, 0);
           vector<int> explorados(n, 0);

         cin >> opcao;
         cin.ignore(50, '\n');

         switch (opcao){
          
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
             cout<<grafo.Distancia(numero_vertice, numero_vertice2)<<endl;
             break;
          
         case 4:
             cout << grafo.Diametro() <<endl;
             break;
          
         case 5:
             grafo.Componente_Conexa();
             break;
          
         case 6:
             break;
          
         default:
             cout << "Por favor, selecione uma dentre as opcoes validas!" <<endl;
             break;
         }

     }while (opcao != 6);
   return 0;
 }

