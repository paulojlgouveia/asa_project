
#include <iostream>
#include <random>

int main() {
	
	int V = 0;
	int E = 0;
	
	int random1 = -1;
	int random2 = -1;
	
	srand(time(NULL));
	
	std::cin >> V;
	std::cin >> E;
	
	std::cout << V << " " << E << std::endl;
	
	for(int t=0; t<E; t++) {
		while(1) {
			random1 = rand()%V;
			random2 = rand()%V;
			
			if(random1 != random2)
				break;
		}
		
		std::cout << random1 << " " << random2 << std::endl;
		
	}
		
	
	return 0;	
}



		int randNum = rand()%(max-min + 1) + min;
