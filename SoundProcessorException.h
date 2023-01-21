#pragma once
#include <exception>
#include <string>

using namespace std;

class SoundProcessorException : public exception {
public:
	SoundProcessorException(const string&);
	SoundProcessorException(const char* msg);
	SoundProcessorException(const char* msg, int err);
	int GetCoderror() const;
	const char* what() const;
private:
	string message;
	int codeError = 0;
};


