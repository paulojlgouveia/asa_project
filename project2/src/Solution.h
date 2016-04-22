#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include <list>

//MERGE_START


// structure representing the solution of the problem
struct Solution {
	int location;
	int totalLoss;
	int *deslocationCost;
	int subsidiariesCount;
	
	Solution(int size): location(-1), totalLoss(99999), subsidiariesCount(size) {
		deslocationCost = new int[size];
		for(int i=0; i<size; i++)
			deslocationCost[i] = 99999;
	}
	
	~Solution() {
		delete[] deslocationCost;
	}
	
	
	void print() {
		for(int t=0; t<subsidiariesCount; t++)
				if(deslocationCost[t] >= 99999)
					totalLoss = 99999;
		
		
		if(totalLoss < 99999) {
			std::cout << location << " " << totalLoss << std::endl;
			for(int t=0; t<subsidiariesCount; t++)
				std::cout << deslocationCost[t] << " ";
		} else {
			std::cout << "N";
		}
		
		std::cout << std::endl;
	}
	
};

//MERGE_END

#endif
