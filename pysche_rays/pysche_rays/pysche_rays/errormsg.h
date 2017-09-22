#pragma once
#include<string>

class Error {
public:
	Error(std::string str) {
		err_str = str;
	}
	const char *toString() const {
		return err_str.c_str();
	}
private:
	std::string err_str;
};
