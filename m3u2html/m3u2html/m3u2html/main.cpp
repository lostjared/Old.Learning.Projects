#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>



void parse(std::string file_name, std::string out_file) {
	std::fstream fin;
	fin.open(file_name.c_str(), std::ios::in );
	std::fstream fout;
	fout.open(out_file.c_str(), std::ios::out );

	if(!fin.is_open() || !fout.is_open()) throw 1;

	fout << "<HTML><TITLE> " << file_name << "</TITLE><BODY>";


	while(!fin.eof()) {
		std::string cur_line;
		std::getline(fin, cur_line);
		if(cur_line.find(",") != -1)
		{
			std::string the_mp3 = cur_line.substr(cur_line.find(",")+1, cur_line.length());

			fout << the_mp3 << "<br>";
			std::cout << the_mp3 << "\n";

		}

	}

	fin.close();
	fout << "</BODY></HTML>";
	fout.close();

}

int main(int argc, char **argv) {

	if(argc == 3) {
		try {
		parse(argv[1], argv[2]);
		}
		catch(int &x) {
			switch(x) {
				case 1:
					std::cout << "Error file could not be opened!\n";
					break;
			}
		}
		catch(...) {
			std::cout << "Error exception thrown!.\n";
		}

#ifdef _WIN32
		system("PAUSE");
#endif

		return 0;
	}

	std::cout << "Error filename invalid or not given!.\n";
#ifdef _WIN32
	system("PAUSE");
#endif

	return 0;
}