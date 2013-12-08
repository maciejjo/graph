#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include <string>
#include <cstdio>

#include "Node.h"

using namespace std;

template <class T> class Graph {

  public:

    int currentNodeId;
    map<string, Node<T> > graphMap;
    vector<vector<bool> > adjMatrix;
    vector<Node<T> *> nodeList;

    Graph() {
      currentNodeId = 0;
    }

    Node<T> addNode() {

      Node<T> *newNode = new Node<T>(currentNodeId);
      vector<bool> newRow;

      for(int i = 0; i < currentNodeId; i++) {
        newRow.push_back(false);
      }

      adjMatrix.push_back(newRow);

      for(unsigned i = 0; i < adjMatrix.size(); i++) {
        adjMatrix[i].push_back(false);
      }

      for(int i = 0; i < nodeList.size(); i++) {
      }
      cout << endl;

      nodeList.push_back(newNode);

      for(int i = 0; i < nodeList.size(); i++) {
      }
      currentNodeId++;
      return *newNode;

    }

    void addArc(Node<T> first, Node<T> second) {
      adjMatrix[first.id][second.id] = true;
    }

    void printAdjMatrix() {
     for(int i = 0; i < currentNodeId; i++) {
      for(int j = 0; j < currentNodeId; j++) {
         cout << adjMatrix[i][j] <<" ";
      }
      cout << endl; 
     }
    }

    class iterator {

      public:

        Node<T> *currentNode;
        vector<bool> visitedNodes;
        bool hasCycle;
        
        iterator() {
          hasCycle = false;
        }

        void findFirst(Graph<T> *g) {
          currentNode = g->nodeList[0];
          cout 
            << "Jestem na wierzchołku " 
            << currentNode->id 
            << endl;

          for(int i = 0; i < g->currentNodeId; i++) {
            if(g->adjMatrix[i][currentNode->id]) {
              cout
                << "Przechodzę na rodzica: "
                << i
                << endl;
              findFirst(g, i);
            }
          }
        }

        void findFirst(Graph<T> *g, int node) {
          currentNode = g->nodeList[node];
          cout 
            << "Jestem na wierzchołku " 
            << currentNode->id 
            << endl;
          for(int i = 0; i < g->currentNodeId; i++) {
            if(g->adjMatrix[i][currentNode->id]) {
              cout
                << "Przechodzę na rodzica: "
                << i
                << endl;
              findFirst(g, i);
            }
          }
        }
          
    };

    iterator begin() {
      iterator newIterator;
      newIterator.findFirst(this);

      /*
      try {
        if(newIterator.hasCycle) {
          throw cyclicgraphexception;
        }
      }
      catch(exception& e) {
      }
      */
      return newIterator;

    }
};

#endif
