#include <cstdio>
#include <cstdlib>

#include <iostream>

#include "Graph.h"
#include "Node.h"

using namespace std;

int main() {

  Graph<string> g;
  Node<string> n1 = g.addNode(), n2 = g.addNode(), n3 = g.addNode();

  *n1 = "Poznań";
  *n2 = "Berlin";
  *n3 = "Paryż";

  g.addArc(n1, n2);
  g.addArc(n2, n3);
  // Ta linia wprowdza cykl
  // g.addArc(n3, n1);

  g.printAdjMatrix();
  cout << endl;

  Graph<string>::iterator it(g.currentNodeId, &g);
  for(it = g.begin(); it != g.end(); it++) {
    cout << *it << endl;

  }
  
  if(g.containsPath(n1, n3)) cout << "Między " << *n1.pointer << " a " << *n3.pointer << " jest ścieżka" << endl;
  if(g.containsPath(n3, n1)) cout << "Między " << *n3.pointer << " a " << *n1.pointer << " jest ścieżka" << endl;
  

  return 0;
}
