#include "mascstd.h"
//#define MASC_APACHE // comment out if not running under apache

int main(int argc, char *argv[]) {
	bool confirm = false;
	if(argc == 2 || argc == 3) {
		masc::BackEnd bend( new masc::Parser(argv[1]) );
		bend.Convert();
		mascstd::SetStdFunc(bend);
#ifdef MASC_APACHE
		cout << "Content-type: text/html\n\n";
#endif
		bool anaylize = true;
		if(argc == 3) {
			if(strcmp(argv[2],"-d") == 0)
			bend.DebugHTML(bend.GetName() + "_debug.html", false);
			else if(strcmp(argv[2], "-dstd") == 0)
				bend.DebugHTML(bend.GetName() + "_debug.html", true);
			else if(strcmp(argv[2], "-dstdn") == 0)
				bend.Debug();
			else if(strcmp(argv[2],"-na") == 0)
				anaylize = false;
			else if(strcmp(argv[2],"-con") == 0)
				confirm = true;
			else {
				std::cout << "Invalid parameter [" << argv[2] << "]  specified\n";
#ifdef _WIN32
#ifndef MASC_APACHE
				system("PAUSE");
#endif
#endif
				return 0;
			}
		}
		bend.Execute(anaylize);
		
		if(confirm == true) {
			std::cout << " Script (" << argv[1] << ") succesfully executed... \n";
		
#ifdef _WIN32
#ifndef MASC_APACHE
			system("PAUSE");
#endif
#endif
		}

	}
	else {
		std::cout << "MasC++ {Master Assembly Script Container++ (written in C++) " << double(masc::version) <<  "}\n\tWritten by Jared Bruni =)\n\temail: jaredbruni@gmail.com\n\nError invalid arguments specified;\n correct argument list is the following\nTo Execute a script: \nmasc sourcefile.msrc\nTo Execute a script and output debug information:\nmasc++ sourcefile.msrc -d\nTo Execute a script and output debug information to stdout\nmasc++ sourcefile.msrc -dstd\nTo output debug information to stdout in plain text:\nmasc++ sourcefile.msrc -dstdn\nTo run with out syntax anaylisis (faster load):\nmasc++ sourcefile.msrc -na\nTo run with confirmiation of succesfull execution:\nmasc++ sourcefile.masc -con\n\n\t\twww.LostSideDead.com\n\n";
#ifdef _WIN32
#ifndef MASC_APACHE
		system("PAUSE");
#endif
#endif
	}
	return 0;
}


