
#include <iostream>

int main() {
	
	int V = 0;
	int E = 0;
	
	int one = -1;
	int two = -1;
		
	std::cin >> V;
	std::cin >> E;
	
	std::cout << 2*V << " " << 1 + 2*E << std::endl;
	
	for(int t=0; t<E; t++) {
		std::cin >> one;
		std::cin >> two;
		
		std::cout << one << " " << two << std::endl;
		std::cout << one+V << " " << two+V << std::endl;
	}
		
	std::cout << V << " " << V+1 << std::endl;

	return 0;	
}
