#pragma once
#include "PCMReader.h"
#include "Mixer.h"
#include "Converter.h"
#include <memory>
#include <string>
#include <map>

using namespace std;

class ConverterFactory {
public:
	ConverterFactory();
	shared_ptr<Converter> GetConverter(const string& converterName);
	void Help();
private:
	map <string, shared_ptr<Converter>> factoryMap;
};

