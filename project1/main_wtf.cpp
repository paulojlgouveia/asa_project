#include <iostream> 
#include <string> //not sure if needed

#include "Node.hpp" 
 
 int main () {
	std::cout << std::endl;
	
	int n_nodes;
	int n_connec;
	std::string s = "112";
	
	//cant convert string to int
	//
	//std::cout << atoi(s.c_str()) << std::endl; 
	
	std::getline(std::cin, s);
	std::cout << s.substr(0, s.find(" ")) << std::endl; //works fine for parsing
	
	n_nodes = 0; //convert parsed string to int
	n_connec = 0;
	
	std::cout << "Num Nodes: " << n_nodes << std::endl;
	std::cout << "Num Connec: " << n_connec << std::endl;

	std::cout << "Nodes Created:";
	while(std::getline(std::cin, s)){
		std::cout << " " << Node(1).getId();
	}
	std::cout << std::endl;
	
	std::cout << std::endl;
	return 0;
 }
