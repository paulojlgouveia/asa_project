#include <iostream>
#include <Graph.h>
#include <Node.h>

class BellmanFord {

	static Node *createSource(Graph *graph){
		Node *source = new Node(0);
		for (int t = 1; t < graph.getNumberOfNodes(); t++)
			source.connect(graph.getNodeAt(t), 0);
		return source;
	}
	
public:

	static void run(Graph *graph){
		Graph.getNodeAt(0) = createSource(graph); // by default source index is zero
		
		BellmanFord.run(graph, 0);
		
		
	}

	
}