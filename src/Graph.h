#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include <stack>
#include <queue>

#include <string>
#include <cstdio>
#include <exception>

#include "Node.h"

using namespace std;


class cyclicgraphexception: public exception {
  public:
    const char *what() const throw() {
      return "Wykryto cykl";
    }
};


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

      nodeList.push_back(newNode);

      currentNodeId++;
      return *newNode;

    }

    void addArc(Node<T> first, Node<T> second) {
      adjMatrix[first.id][second.id] = true;
      first.addNext(second);
      second.addPrev(first);

    }
    
    bool containsPath(Node<T> first, Node<T> second) {
      if(adjMatrix[first.id][second.id])
        return true;

      bool foundPath = false;
      for(int i = 0; i < currentNodeId; i++) {
        if(adjMatrix[first.id][i] && containsPath(*nodeList[i], second)) {
          foundPath = true;
          break;
        }
      }
      if(foundPath) return true;
      else return false;
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
        Graph<T> *graph;
        int currentPos;
        int currentNodeNum;
        vector<bool> visitedNodes;
        vector<int> nodeResult;
        stack<int> tmp_stack, result;
        bool hasCycle;
        
        iterator(int nodes, Graph<T> *g) {
          hasCycle = false;
          graph = g;
          for(int i = 0; i < nodes; i++) {
            visitedNodes.push_back(false);
          }
        }

        void clearVisited() {

          for(int i = 0; i < graph->currentNodeId; i++) {
            visitedNodes[i] = (false);
          }
        }


        void traverseDfs(Graph<T> *graph, int node) {

          for(int i = 0; i < graph->currentNodeId; i++) {
            if(graph->adjMatrix[i][node] && !visitedNodes[i]) {
              traverseDfs(graph, i);
            }
          }

          if(!visitedNodes[node]) {
            visitedNodes[node] = true;
            tmp_stack.push(node);
          }
              
          for(int i = 0; i < graph->currentNodeId; i++) {
            if(graph->adjMatrix[node][i] && !visitedNodes[i]) {
              traverseDfs(graph, i);
            }
          }
        }


        void detectCycle() {
          for(int i = 0; i < graph->currentNodeId; i++) {
            if(hasCycle) break;
              clearVisited();
              detectCycle(i);
          }
        }

        void detectCycle(int node) {

          if(visitedNodes[node]) hasCycle = true;
          else {
            visitedNodes[node] = true;
            for(int i = 0; i < graph->currentNodeId; i++) {
              if(graph->adjMatrix[i][node]) {
                detectCycle(i);
              }
            }
          }
        }
          
        

        void operator ++(int) {
          result.pop();
          currentNodeNum = result.top();
          currentNode = graph->nodeList[currentNodeNum];
        }

        bool operator != (iterator i) {
          if(i.currentNodeNum != currentNodeNum)
            return true;
          else
            return false;
        }

        T operator*() { return *currentNode->pointer; }

    };

    iterator begin() {
      iterator newIterator(currentNodeId, this);

      newIterator.detectCycle();
      cyclicgraphexception cge;

      try {

        if(newIterator.hasCycle)
          throw cge;

        newIterator.clearVisited();

        for(int i = 0; i < currentNodeId; i++) {
          if(!newIterator.visitedNodes[i]) {
            newIterator.traverseDfs(this, 0);
          }
        }

        newIterator.tmp_stack.push(-1);
        while(!newIterator.tmp_stack.empty()) {
          newIterator.result.push(newIterator.tmp_stack.top());
          newIterator.tmp_stack.pop();
        }

        newIterator.currentNode = nodeList[newIterator.result.top()];
        newIterator.currentPos = 0;
        newIterator.currentNodeNum = newIterator.result.top();

        return newIterator;
      }

      catch(exception& e) {
        terminate();
      }

    }

    iterator end() {
      iterator newIterator(currentNodeId, this);
      newIterator.currentNodeNum = -1;
      return newIterator;
    }


      /*
      try {
        if(newIterator.hasCycle) {
          throw cyclicgraphexception;
        }
      }
      catch(exception& e) {
      }
      */
};

#endif
