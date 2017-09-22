#include "strMetric.h"

strMetrics::strMetrics() : std::string() {}
strMetrics::strMetrics( std::string s ) : std::string(s) {}

int strMetrics::countVowels()
{
	int cnt = 0;
	const char * s = this->c_str();
	for(size_t i = 0; i < strlen(s); i++)
	{
		char c = tolower(s[i]);
		if(c == 'a' || c == 'e' || c == 'i' || c =='o' || c == 'u')
			cnt++;
	}
	return cnt;
}

int strMetrics::length()
{
	return int(strlen(this->c_str()));
}
int strMetrics::Upper()
{
	std::string::iterator i;
    for(i = begin(); i != end(); i++)
		*i = toupper(*i);
	return length();
}
int strMetrics::Lower()
{
	std::string::iterator i;
	for(i = begin(); i != end(); i++)
		*i = tolower(*i);
	return length();
}
int strMetrics::sumChars()
{
	int total = 0;
	std::string::iterator i;
	for(i = begin(); i != end(); i++)
		total += *i;
	return total;
}

strMetrics& strMetrics::operator=(std::string &s) {
	assign(s.begin(),s.end());
	return *this;
}

strMetrics& strMetrics::operator=(const char *s) {
	std::string str = s;
	assign(str.begin(),str.end());
	return *this;
}