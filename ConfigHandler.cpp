#include "ConfigHandler.h"
#include "StringUtilities.h"
#include "Converter.h"
#include "ConverterFactory.h"
#include "PCMReader.h"
#include "PCMWriter.h"
#include "SoundProcessorException.h"
#include <memory>
#include <vector>
#include <iostream>

using namespace std;

ConfigHandler::ConfigHandler(const string& fileName) : configFile(fileName)
{
	if (!configFile.is_open()) {
		throw SoundProcessorException("file " + fileName + " not open");
	}
}

void ConfigHandler::Handle(const vector<string>& fileNameVector) {
	const string& outputFileName = fileNameVector[0];
	string command;
	ConverterFactory converterFactory;

	vector<shared_ptr<PCMReader>> sourceFileVector = GetSourceFileVector(fileNameVector);

	shared_ptr<Converter> curConverter = sourceFileVector[0];
	vector<shared_ptr<Converter>> converterOperandVector(1);
	converterOperandVector[0] = curConverter;
	vector<string> stringOperandVector;

	do {
		getline(configFile, command);
		if (command == "") {
			break;
		}
		stringOperandVector.clear();
		vector<string> cmdVec = StringUtilities::Split(command);
		shared_ptr<Converter> converter = converterFactory.GetConverter(cmdVec[0]);

		FillConverterAndStringOperandVectors(converterOperandVector, stringOperandVector, cmdVec, sourceFileVector);

		converter->JoinSource(converterOperandVector, stringOperandVector);
		curConverter = converter;
		converterOperandVector.resize(1);
		converterOperandVector[0] = curConverter;
	} while (!configFile.eof());

	PCMWriter writer(outputFileName, curConverter);
	writer.FullWrite();

	configFile.close();
}

vector<shared_ptr<PCMReader>> ConfigHandler::GetSourceFileVector(
	const vector<string>& fileNameVector) 
{
	vector< shared_ptr<PCMReader> > sourceFileVector(fileNameVector.size() - 1);
	for (int i = 0; i < fileNameVector.size() - 1; i++) {
		sourceFileVector[i] = make_shared<PCMReader>();
		sourceFileVector[i]->Open(fileNameVector[i + 1]);
	}
	return sourceFileVector;
}

void ConfigHandler::FillConverterAndStringOperandVectors(
	vector<shared_ptr<Converter>>& convVec,
	vector<string>& strVec,
	const vector<string>& cmdVec,
	const vector<shared_ptr<PCMReader>>& sourceVec)
{
	for (auto word : cmdVec) {
		if (word[0] == '$') {
			int inputFileNumber = stoi(word.substr(1));
			convVec.push_back(sourceVec[inputFileNumber - 1]);
		}
		else {
			if (StringUtilities::IsNumber(word))
				strVec.push_back(word);
		}
	}
}
