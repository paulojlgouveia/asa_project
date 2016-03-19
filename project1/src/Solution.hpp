#ifndef __SOLUTION_H__
#define __SOLUTION_H__

//MERGE_START
// structure representing the solution of our problem
struct Solution {
	int minId;
	int maxId;
	int articulationNodes;
	
	Solution(): minId(-1), maxId(-1), articulationNodes(0) {}
	~Solution() {}
};
//MERGE_END

#endif
