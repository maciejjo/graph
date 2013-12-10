#ifndef NODE_H
#define NODE_H

#include <list>

using namespace std;

template <class T> class Graph;

template <class T> class Node {

  public:
    T *pointer;
    int id;
    Graph<T> *g;
    list<Node<T> > *next_list;
    list<Node<T> > *prev_list;


    Node(int NodeId, Graph<T> *graph) {
      id = NodeId; 
      g = graph; 
      next_list = new list<Node<T> >;
      prev_list = new list<Node<T> >;
      pointer = new T;
    }

    ~Node() {
    }

    void addNext(Node<T> element) {
      next_list->push_back(element);
    }

    void addPrev(Node<T> element) {
      prev_list->push_back(element);
    }

    const list<Node<T> > nexts() {
      return *next_list;
    }

    const list<Node<T> > prevs() {
      return *prev_list;
    }

    T& operator*() { 
      return *pointer; 
    }

    void setLabel(string label) {
      g->graphMap.insert(pair<string,Node<T>* >(label, this));
    }
};

#endif
