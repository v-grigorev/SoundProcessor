#pragma once
#include "Converter.h"

class Mute : public Converter{
public:
	short* GetData(long int offset, long int length);
	void SingleConvert(vector<short*> dataVec, long int length);
	void JoinSource(vector<shared_ptr<Converter>> converterVec, vector<string> argv);
	string Help();
private:
	shared_ptr<Converter> source;
	long int startMute = 0;
	long int endMute = 0;
};

