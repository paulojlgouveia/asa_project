#ifndef __SOLUTION_H__
#define __SOLUTION_H__


// solution container
struct Solution {
	int minID;
	int maxID;
	int artNodesCounter;
	
	Solution(): minID(-1), maxID(-1), artNodesCounter(0) {}
	~Solution() {}
};

#endif