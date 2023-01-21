#include <iostream>
#include <memory>
#include "PCMReader.h"
#include "ConfigHandler.h"
#include "SoundProcessorException.h"
#include "ConverterFactory.h"
#include <vector>
#include <string>
#include <iostream>
#define START_DATA 22

using namespace std;

int main(int argc, char* argv[]) {
	if (string(argv[1]) == string("-h")) {
		ConverterFactory factory;
		factory.Help();
		return 0;
	}
	try {
		ConfigHandler configHandler(argv[1]);
		vector<string> cmdVec(argc - 2);
		for (int i = 0; i < argc - 2; i++) {
			cmdVec[i] = (argv[i + 2]);
		}
		configHandler.Handle(cmdVec);
	}
	catch (SoundProcessorException(e)) {
		puts(e.what());
	}
	
	
	return 0;
}