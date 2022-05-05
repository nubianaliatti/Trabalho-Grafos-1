
#include "Edge.h"
#include "Graph.h"
#include "Node.h"
#include "Tools.h"
#include <iostream>
#include <fstream>

using namespace std;
//**************************************************************************************************
//! * Defining the Graph's methods
//**************************************************************************************************/

//! Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node)
{
    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;
    this->position = 0;
}

//! Destructor
Graph::~Graph()
{
    Node *next_node = this->first_node;

    while (next_node != nullptr)
    {
        next_node->removeAllEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

//! Getters --------------------------------------------------------------------------------------------

int Graph::getOrder()
{
    return this->order;
}
int Graph::getNumberEdges()
{
    return this->number_edges;
}

//Function that verifies if the graph is directed
bool Graph::getDirected()
{
    return this->directed;
}

//Function that verifies if the graph is weighted at the edges
bool Graph::getWeightedEdge()
{
    return this->weighted_edge;
}

//Function that verifies if the graph is weighted at the nodes
bool Graph::getWeightedNode()
{
    return this->weighted_node;
}

Node *Graph::getFirstNode()
{
    return this->first_node;
}

Node *Graph::getLastNode()
{
    return this->last_node;
}

Node *Graph::getNode(int id)
{
    //cria ponteiro para percorrer a lista de nodes
    Node *node = first_node;

    //encontra o node com o id desejado
    while (node != nullptr)
    {
        if (node->getId() == id)
            return node;
        node = node->getNextNode();
    }

    //retorna o node ou null caso nao encontre
    return nullptr;
}
Node *Graph::getNodePosition(int position)
{
    //cria ponteiro para percorrer a lista de nodes
    Node *node = first_node;

    //encontra o node com o id desejado
    while (node != nullptr)
    {
        if (node->getPosition() == position)
            return node;

        node = node->getNextNode();
    }

    //retorna o node ou null caso nao encontre
    return nullptr;
}

void Graph::insertNode(int id)
{
    //confere se o grafo tem nodes
    if (first_node != nullptr)
    {
        //caso tenha, cria um novo node, aponta o ultimo pro novo e o novo de torna o ultimo
        Node *novo_node = new Node(id);
        novo_node->setPosition(this->position);
        last_node->setNextNode(novo_node);
        last_node = novo_node;
    }
    else
    {
        //caso nao tenha, cria um novo node e ele se torna o ultimo e o primeiro
        Node *novo_node = new Node(id);
        novo_node->setPosition(this->position);
        first_node = novo_node;
        last_node = novo_node;
    }
    this->position = this->position + 1;
}

void Graph::insertEdge(int id, int target_id, float weight)
{
    //cria um ponteiro para o node desejado e o um auxiliar para o node alvo da aresta
    Node *node = getNode(id);
    Node *aux = getNode(target_id);

    if (node == nullptr)
    {
        this->insertNode(id);
        node = last_node;
    }
    if (aux == nullptr)
    {
        this->insertNode(target_id);
        aux = last_node;
    }
    //confere se os nodes existem
    if (node != nullptr && aux != nullptr)
    {

        //confere se a aresta já existe
        if (!node->searchEdge(target_id))
        {
            //caso o node exista mas a aresta nao, insere a aresta
            node->insertEdge(target_id, aux->getPosition(), weight);

            this->number_edges++;

            // se o grafo for nao-direcionado e nao houver aresta de volta
            if (this->directed == 0 && !aux->searchEdge(id))
            {
                //insere a aresta de volta
                aux->insertEdge(id, node->getPosition(), weight);
            }
        }
    }
}

void Graph::removeNode(int id)
{
    //cria um ponteiro para o node desejado
    Node *node = getNode(id);

    //retorna caso nao exista o node desejado
    if (node == nullptr)
        return;
    else if (node == first_node) //se o node eh o primeiro, apenas faz o proximo ser o primeiro
        first_node = node->getNextNode();
    else
    {
        //caso seja um node do meio ou o ultimo, cria um ponteiro auxiliar
        Node *aux = first_node;

        //encontra o node anterior ao node desejado
        while (aux->getNextNode() != node)
            aux = aux->getNextNode();

        //se o no desejado for o ultimo, atualiza o ultimo para o anterior
        if (node == last_node)
            last_node = aux;

        //seta o proximo de anterior para o proximo do desejado
        aux->setNextNode(node->getNextNode());
    }

    //deleta o node desejado
    delete node;
}

bool Graph::searchNode(int id)
{
    //cria um ponteiro para o node desejado
    Node *node = getNode(id);

    //retorna falso caso nao encontre e verdadeiro caso encontre
    if (node == nullptr)
        return false;
    else
        return true;
}

void Graph::cleanVisited()
{
    /**
     * @brief Função para definir todos os nós do grafo como não visitados.
     * 
     */

    Node *node = this->getFirstNode(); // Ponteiro que armazena o endereço de memória do primeiro nó do grafo.

    // Realiza a operação para todos os nós do grafo.
    while (node != nullptr)
    {
        node->setVisited(false);    // Define o nó como não visitado.
        node = node->getNextNode(); // Ponteiro passa a apontar para o próximo nó do grafo.
    }
}
