#ifndef _MXSDLMSG_H__
#define _MXSDLMSG_H__
#ifdef _WIN32
#include<windows.h>
#endif
#include<string>
#include<sstream>
class ErrorMsg {
public:
	ErrorMsg(std::string err) {
		str_val = err;
	}

	void PrintLastError() {
		std::ostringstream ss;
		ss << "Unhandled Exception: " <<  str_val << "\n";
#ifdef _WIN32
		MessageBox(GetForegroundWindow(),ss.str().c_str(),"Unhandled Exception", MB_OK | MB_ICONERROR);
#else
		std::cout << ss.str();
#endif
	}
protected:
	std::string str_val;
};

class Message {
public:
	Message() {
		str = "";
		caption = "";
	}
	Message(std::string str, std::string caption) {
		this->str = str, this->caption = caption;
	}

	void SendMessage() {
#ifdef _WIN32
		MessageBox(GetForegroundWindow(), str.c_str(), caption.c_str(), MB_ICONINFORMATION);
#else
		std::cout << caption << " : " << str << "\n";
#endif
	}
	void DebugMessage() {
		std::ostringstream ss;
		ss << caption << " : " << str << "\n";
#ifdef _WIN32
		OutputDebugString(ss.str().c_str());
#else
		std::cout << ss.str();
#endif
	}
	Message &operator<<(std::string s) {
		std::ostringstream ss;
		ss << str << s;
		str = ss.str();
		return *this;
	}

	Message &operator<<(int x) {
		std::ostringstream ss;
		ss << str << x;
		str = ss.str();
		return *this;
	}

	Message &operator<<(float x) {
		std::ostringstream ss;
		ss << str << x;
		str = ss.str();
		return *this;
	}
	Message &operator=(std::string s) {
		caption = s;
		return *this;
	}
	Message &operator+=(std::string s) {
		caption += s;
		return *this;
	}
	void clear() {
		str = "";
	}
	void flush() {
		str = "";
		caption = "";
	}
protected:
	std::string str,caption;
};

#endif
