/**********************************************************************/
/** Merge several files into a single one. Only lines between tokens **/
/** will be merged. Put all the includes into a separate file.  	 **/ 
/**	Developed by: DanielFigueira									 **/
/**********************************************************************/
#include <iostream> 
#include <fstream>

#define START_TOKEN "//MERGE_START"
#define END_TOKEN "//MERGE_END"
#define USE_SEPARATORS true

 int main (int argc, char* argv[]) {
	std::string line;
	std::ifstream inputFile;
	std::ofstream outputFile;
	bool print;
	bool empty;

	if(argc < 3){
		std::cout << "Usage: ./" << argv[0] << " output_file input_files" << std::endl;
		return 1;
	}

	outputFile.open(argv[1], std::ios::trunc);
	if(!outputFile.is_open()){
		std::cout << "Error: Can't open output file. Terminating..." << std::endl;
		return 2;
	}
	
	for (int i = 2; i < argc; i++){
			
		inputFile.open(argv[i]);
		if(!inputFile.is_open()){
			std::cout << "Error: Can't open input file. Terminating..." << std::endl;
			outputFile.close();
			return 3;
		}
		
		std::cout << "Merging " << argv[i] << "...";
		if(USE_SEPARATORS)
			outputFile << std::endl << "/*************************** "
			<< argv[i] << " ***************************/" << std::endl;
		
		print = false;
		empty = true;
		
		while (std::getline(inputFile, line)) {
			if(line.find(START_TOKEN) != 
			std::string::npos){
				print = true;
				empty = false;
				outputFile << std::endl;
				continue;
			}
			if(line.find(END_TOKEN) != std::string::npos){
				print = false;
				outputFile << std::endl;
				continue;
			}
			
			if(print)
				outputFile << line << std::endl;
		}
		
		inputFile.close();
		
		if (empty)
			std::cout << " No tags found" << std::endl;
		else
			std::cout << " Done" << std::endl;
	
	}
	
	std::cout << "Output file: " << argv[1] << std::endl;
	
	outputFile.close();
	
	return 0;
}
