#include <iostream>
#include <Graph.h>
#include <Node.h>

class BellmanFord {
	
private:

	static void initializeSingleSource(Graph *graph, Node *source){
		source.setCost(0);
		for (int t = 0; t < graph.getNumberOfNodes(); t++)
			graph.getNodeAt(t).setCost(99999); //FIXME : CLIMITS?
	}
	
	static void relax(Node *u, Node *v, int weight){
		if (v.getPathCost() > u.getPathCost() + weight) {
			v.setPathCost(u.getPathCost() + weight)
			v.setParent(u);
		}
	}
	
public:
	
	// runs bellman-ford algorithm starting at node with given id
	static void run(Graph *graph, int id){
		Node *u:
		Node *v;
		int weight;
		
		initializeSingleSource(graph, graph.getNodeAt(0));
		
		for (int t = 1; t < graph.getNumberOfNodes(); t++){
			
			// FIXME: INSERT LOOP HERE
			// 		RELAX();
		}
		
		// doesn't check for negative loops since there's no need
	}
}