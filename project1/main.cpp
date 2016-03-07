
#include <iostream> 
#include <fstream>

#include "Node.h" 
 
 int main () {
	std::cout << std::endl;
	
	std::string s;
	std::getline(std::cin, s);
	
	std::cout << s << std::endl;
	
	Node node = Node(123);
	
	std::cout << node.getId() << std::endl;
	
	std::cout << std::endl;
	return 0;
 }