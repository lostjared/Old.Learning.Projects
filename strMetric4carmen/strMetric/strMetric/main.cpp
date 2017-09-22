// Example driver for a friend
#include "strMetric.h"
#include<string>
#include<iostream>

using std::cout;
using std::cin;
using std::endl;


std::ostream& operator<<(std::ostream& out, const strMetrics &s) {
	out << s.c_str();
	return out;
}

std::istream& operator>>(std::istream& in, strMetrics &s) {
	std::string str;
	in >> str;
	s = str;
	return in;
}

int main() {
	strMetrics s;
	cout << "Enter a word 1 token: ";
	cin >> s;
	cout << "Vowels: " << s.countVowels() << " Sum: " << s.sumChars() << endl;
	cout << "Length of string: " << s.length() << endl;
	s.Lower();
	cout << "Lowercased: " << s;
	s.Upper();
	cout << " Uppercased: " << s << endl;
	cout << "Goodbye!\n";
	system("PAUSE");
	return 0;
}