#include "PCMWriter.h"
#include "SoundProcessorException.h"
#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

PCMWriter::PCMWriter(const string& fileName, shared_ptr<Converter> newSource) {
	file = fopen(fileName.data(), "wb");
	if (file == NULL) {
		throw SoundProcessorException("file " + fileName + " not open");
	}
	source = newSource;
}

void PCMWriter::Write(long int offset, long int length) {
	short* data = source->GetData(offset, length);
	long int writeCount = source->GetNumberOfRead();
	fwrite(data, sizeof(short), writeCount, file);
	if (writeCount != length) {
		sourceIsEnded = true;
	}
	free(data);
}

void PCMWriter::FullWrite() {
	long int offset = 0;
	long int length = 10000;
	do {
		Write(offset, length);
		offset += length;
	} while (!sourceIsEnded);
}
