#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Converter.h"

using namespace std;

class Converter {
public:
	virtual short* GetData(long int offset, long int length) = 0;
	virtual void SingleConvert(vector<short*> dataVec, long int length) = 0;
	virtual void JoinSource(vector<shared_ptr<Converter>> converterVec, vector<string> argv) = 0;
	long int GetNumberOfRead() const;
	void IntervalHandle(vector<short*> dataVec, long int offset, long int length, long int startInterval, long int endInterval);
protected:
	long int readCount = 0;
};

