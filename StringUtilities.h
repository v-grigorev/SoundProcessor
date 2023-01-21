#pragma once
#include <string>
#include <vector>

using namespace std;

class StringUtilities {
public:
    static bool IsNumber(const string& str);
	static vector<string> Split(const string& cmdLine);
};

