#ifndef _STRMETRIC_H_
#define _STRMETRIC_H_

#include<string>
#include<ctype.h>

class strMetrics : public std::string
{
public:
	    strMetrics();
		strMetrics( std::string s );
		int countVowels();
		int length();
		int Upper();
		int Lower();
		int sumChars();
		strMetrics& operator=(std::string &s);
		strMetrics& operator=(const char *s);
};
#endif