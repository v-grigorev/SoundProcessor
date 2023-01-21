#include "PCMReader.h"
#include "SoundProcessorException.h"
#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

PCMReader::~PCMReader() {
	//fclose(file);
}

void PCMReader::Open(const string& fileName) {
	file = fopen(fileName.data(), "rb");
	if (file == NULL) {
		throw SoundProcessorException("file " + fileName + " not open");
	}
}

void PCMReader::JoinSource(vector<shared_ptr<Converter>> converterVec, vector<string> argv) {

}

short* PCMReader::GetData(long int offset, long int length) {
	short* out = new short[length];
	fseek(file, 44 + offset * sizeof(short), SEEK_SET);
	readCount = fread(out, sizeof(short), length, file);
	return out;
}

void PCMReader::SingleConvert(vector<short*> dataVec, long int lenght) {

}
