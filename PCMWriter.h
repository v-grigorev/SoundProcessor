#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Converter.h"

using namespace std;

class PCMWriter {
public:
	PCMWriter(const string& fileName, shared_ptr<Converter> source);
	void Write(long int offset, long int length);
	void FullWrite();
private:
	FILE* file;
	shared_ptr<Converter> source;
	bool sourceIsEnded = false;
};

