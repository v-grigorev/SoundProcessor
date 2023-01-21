#pragma once
#include "Converter.h"
#include "FourierDecomposition.h"

class Equalizer : public Converter {
public:
	short* GetData(long int offset, long int length);
	void SingleConvert(vector<short*> dataVec, long int length);
	void JoinSource(vector<shared_ptr<Converter>> converterVec, vector<string> argv);
	string Help();
private:
	shared_ptr<Converter> source;

	long int startInterval = -1;
	long int endInterval = -1;

	long int startEqualize = -1;
	long int endEqualize = -1;

	int percent—hange = -1;
};

