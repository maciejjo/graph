#include <cstdio>
#include <cstdlib>

#include <iostream>

#include "Graph.h"
#include "Node.h"

using namespace std;

int main() {

  Graph<string> g;
  Node<string> n1 = g.addNode(), n2 = g.addNode(), n3 = g.addNode(), 
    n4 = g.addNode();

  *n1 = "Poznań";
  *n2 = "Berlin";
  *n3 = "Paryż";
  *n4 = "Mozambik";

  g.addArc(n2,n1);
  g.addArc(n3,n2);

  g.printAdjMatrix();
  cout << endl;
  for(unsigned i; i < g.nodeList.size(); i++) {
    cout << g.nodeList[i].id << endl;
  }

  Graph<string>::iterator it;
  it = g.begin();
  

  return 0;
}
