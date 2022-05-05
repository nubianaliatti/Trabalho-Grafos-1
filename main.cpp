#include <iostream>
#include "Graph.h"
#include <fstream>

using namespace std;

Graph *leitura(ifstream &input_file, int directed, int weightedEdge, int weightedNode) {

  //Variáveis para auxiliar na criação dos nós no Grafo
  int idNodeSource;
  int idNodeTarget;
  int order;
  int numEdges;
  float edgeWeight;

  //Pegando a ordem do grafo
  input_file >> order;

  cout << "\nLendo o arquivo input.txt..." << endl;
  //cout << "Ordem: " << order << endl;

  //Criando objeto grafo: Ordem - direcionado - peso Aresta - peso Nó
  Graph *graph = new Graph(order, directed, weightedEdge, weightedNode);

  //Leitura de arquivo
  if (!graph->getWeightedEdge() && !graph->getWeightedNode()) // Sem peso nas arestas e sem peso nos nós
  {

    while (input_file >> idNodeSource >> idNodeTarget) {
      //cout << "Edge: " << idNodeSource << " -- " << idNodeTarget << endl;
      graph->insertEdge(idNodeSource, idNodeTarget, 0);
    }
  } else if (graph->getWeightedEdge() && !graph->getWeightedNode()) // Com peso nas arestas e sem peso nos nós
  {
    while (input_file >> idNodeSource >> idNodeTarget >> edgeWeight) {
      //cout << "Edge: " << idNodeSource << " - " << idNodeTarget << " - " << edgeWeight << endl;
      graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
    }
  } else if (graph->getWeightedNode() && !graph->getWeightedEdge()) // Com peso no nó e sem peso na aresta
  {
    float nodeSourceWeight, nodeTargetWeight;

    while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight) {
      graph->insertEdge(idNodeSource, idNodeTarget, 0);
      graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
      graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
    }
  } else if (graph->getWeightedNode() && graph->getWeightedEdge()) // Com peso no nó e com peso na aresta
  {

    float nodeSourceWeight, nodeTargetWeight, edgeWeight;

    while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight) {
      graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
      graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
      graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
    }
  }

  return graph;
}

int menu() {

  int selecao;

  cout << "\nMENU" << endl;
  cout << "----" << endl;
  cout << "[1]  Fecho Transitivo Direto" << endl;
  cout << "[2]  Fecho Transitivo Indireto" << endl;
  cout << "[3]  Caminho Mínimo entre dois vértices - Dijkstra" << endl;
  cout << "[4]  Caminho Mínimo entre dois vértices - Floyd" << endl;
  cout << "[5]  Árvore Geradora Mínima sobre subgrafo vertice induzido por X usando algoritmo de Prim" << endl;
  cout << "[6]  Árvore Geradora Mínima sobre subgrafo vertice induzido por X usando algoritmo de Kruskal" << endl;
  cout << "[7]  Caminhamento Profundidade destacando as Arestas de retorno" << endl;
  cout << "[8]  Ordenação topologica em D ou a informação de que não é um grafo acíclico direcionado" << endl;
  cout << "[9]  Algoritmo Guloso" << endl;
  cout << "[10] Algoritmo Guloso Randomizado " << endl;
  cout << "[11] Algoritmo Guloso Randomizado Reativo" << endl;
  cout << "[12] Algoritmo Guloso 2" << endl;
  cout << "[13] Algoritmo Guloso 2 Randomizado " << endl;
  cout << "[14] Algoritmo Guloso 2 Randomizado Reativo" << endl;
  cout << "[0]  Sair" << endl;

  cout << "\nSua opção: ";
  cin >> selecao;

  return selecao;
}
int main(int argc, char const *argv[]) {
  //Verificação se todos os parâmetros do programa foram entrados
  if (argc != 6) {
    cout << "ERRO: Esperado: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
    return 1;
  }

  string program_name(argv[0]);
  string input_file_name(argv[1]);

  string instance;
  if (input_file_name.find("v") <= input_file_name.size()) {
    string instance = input_file_name.substr(input_file_name.find("v"));
    cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
  }

  //Abrindo arquivo de entrada
  ifstream input_file;
  ofstream output_file;
  input_file.open(argv[1], ios::in);
  output_file.open(argv[2], ios::out | ios::trunc);

  Graph *graph;

  if (input_file.is_open()) {
    graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
  } else
    cout << "Não foi possível abrir o arquivo! " << argv[1];

  string d, a, v;
  d = a = v = "Sim";

  int o = graph->getDirected();
  int e = graph->getWeightedEdge();
  int n = graph->getWeightedNode();

  if (!o)
    d = "Não";
  if (!e)
    a = "Não";
  if (!n)
    v = "Não";

  cout << "\nCriando grafo..." << endl;
  cout << "Ordem: " << graph->getOrder() << endl;
  cout << "Nº Arestas: " << graph->getNumberEdges() << endl;
  cout << "Direcionado? " << d << endl;
  cout << "Arestas com peso? " << a << endl;
  cout << "Vertices com peso? " << v << endl;

  return 0;
}
