#ifndef NODE_H
#define NODE_H

template <class T> class Node {

  public:
    T *pointer;
    int id;

    Node(int NodeId) {
      id = NodeId; 
      pointer = new T;
    }

    T& operator*() { 
      return *pointer; 
    }
};

#endif
