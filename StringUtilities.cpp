#include "StringUtilities.h"
#include <regex>

bool StringUtilities::IsNumber(const string& str) {
    for (auto j : str) {
        if (!isdigit(j))
            return false;
    }
    return true;
}

vector<string> StringUtilities::Split(const string& cmdLine) {
	vector<string> out;
	const regex wordRegular("[a-zA-Z0-9.-/$]+");
	sregex_iterator beg(cmdLine.cbegin(), cmdLine.cend(), wordRegular);
	sregex_iterator end;
	for (auto i = beg; i != end; ++i) {
		out.push_back(i->str());
	}
	return out;
}
