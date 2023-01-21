#pragma once
#include "Converter.h"
#include <vector>
#include <memory>
#include <string>

using namespace std;

class Mixer : public Converter {
public:
	short* GetData(long int offset, long int length);
	void SingleConvert(vector<short*> dataVec, long int lenght);
	void JoinSource(vector< shared_ptr<Converter> > converterVec, vector<string> argv);
	string Help();
private:
	bool additionalSourceIsEnded = false;
	long int convertOffset = -1;
	shared_ptr<Converter> mainSource;
	shared_ptr<Converter> additionalSource;
};

