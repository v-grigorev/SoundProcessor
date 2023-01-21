#pragma once
#include <vector>
#include <string>
#include "Converter.h"

using namespace std;

class PCMReader : public Converter {
public:
	~PCMReader();
	void Open(const string& fileName);
	short* GetData(long int start, long int length);
	void SingleConvert(vector<short*> dataVec, long int lenght);
	void JoinSource(vector< shared_ptr<Converter> > converterVec, vector<string> argv);
private:
	FILE* file;
};

