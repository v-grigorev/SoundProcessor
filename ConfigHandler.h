#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "PCMReader.h"

using namespace std;

class ConfigHandler {
public:
	ConfigHandler(const string& fileName);
	void Handle(const vector<string>& operandVec);
private:
	ifstream configFile;
	static vector<shared_ptr<PCMReader>> GetSourceFileVector(const vector<string>& fileNameVector);
	static void FillConverterAndStringOperandVectors(vector<shared_ptr<Converter>>& conv, vector<string>& str, const vector<string>& cmd, const vector<shared_ptr<PCMReader>>& readers);
};

