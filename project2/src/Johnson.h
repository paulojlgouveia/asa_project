#include <iostream>
#include <Graph.h>
#include <Node.h>

class BellmanFord {
	
private:

	static Node *createSource(Graph *graph){
		Node *source = new Node(0);
		for (int t = 0; t < graph.getNumberOfNodes(); t++)
			source.connect(graph.getNodeAt(t), 0);
	}
	
public:

	
}