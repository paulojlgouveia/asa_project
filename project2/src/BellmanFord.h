#include <iostream>
#include <Graph.h>
#include <Node.h>

class BellmanFord {
	
private:
	static void initializeSingleSource(Graph *graph, Node *source){
		source.setCost(0);
		for (int t = 0; t < graph.getNumberOfNodes(); t++)
			graphGetNodeAt(t).setCost(NULL);
	}
	
	static void relax(Node *u, Node *v, int weight){
		if (v.getCost() > u.getCost() + weight) {
			v.setCost(u.getCost() + weight)
			v.setParent(u);
		}
	}
	
public:
	
	// runs bellman-ford algorithm starting at node with given id
	static bool run(Graph *graph, int id){
		
		
		
	}
		
	
	
	
	
}