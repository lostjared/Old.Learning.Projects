#include "toke.h"


int main(int argc, char **argv) {

	if(argc == 3 && strcmp(argv[1],"-c") == 0) {
		file_buffer fbuf(argv[2]);
		text_buffer buff(fbuf.get_str());
		Scanner scan(&buff);
		scan.PrintTokens();
		std::fstream file;
		
		file.open(std::string(std::string(argv[2]) + ".html").c_str(), std::ios::out );
		if(file.is_open()) 
			scan.OutputHTML(file);
		file.close();
	}
	return 0;
}
