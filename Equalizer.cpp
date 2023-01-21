#include "Equalizer.h"
#include "SoundProcessorException.h"
#include "StringUtilities.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define OVER_READ 1000

short* Equalizer::GetData(long int offset, long int length) {
	if (offset == 0) {
		short* data = source->GetData(offset, length + OVER_READ);
		readCount = source->GetNumberOfRead();

		vector<short*> dataVec;
		dataVec.push_back(data);

		IntervalHandle(dataVec, offset, readCount, startInterval, endInterval);
		if (readCount > length) {
			readCount = length;
		}
		return data;
	}
	else {
		short* data = source->GetData(offset - OVER_READ, length + 2 * OVER_READ);
		readCount = source->GetNumberOfRead();

		vector<short*> dataVec;
		dataVec.push_back(data);

		IntervalHandle(dataVec, offset - OVER_READ, readCount, startInterval, endInterval);

		short* newData = (short*)malloc(sizeof(short) * length);
		
		if (readCount < length + OVER_READ) {
			readCount -= OVER_READ;
		}
		else {
			readCount = length;
		}
		memcpy(newData, data + OVER_READ, readCount * sizeof(short));
		return newData;
		
	}
}

void Equalizer::SingleConvert(vector<short*> dataVec, long int length) {
	short* data = dataVec[0];
	float factor = (float)percent—hange / 100;

	FourierDecomposition decomposition;
	decomposition.DoDecompose(data, length, 2000);
	vector<double> sinCoef = decomposition.GetSinVec();
	vector<double> cosCoef = decomposition.GetCosVec();

	double frequency = (M_PI * 2) / length;

	for (int i = 0; i < length; i++) {
		double res = 0;
		res += cosCoef[0] / 2;
		for (int j = 1; j < 2000; j++) {
			double sinC = sinCoef[j] * sin(i * j * frequency);
			double cosC = cosCoef[j] * cos(i * j * frequency);
			double sumCoef = sinC + cosC;
			if (j * (44100 / length) > startEqualize && j * (44100 / length) < endEqualize) {
				sumCoef *= factor;
			}
			res += sumCoef;
		}

		if (res > 32766) {
			data[i] = 32766;
		}
		else if (res < -32766) {
			data[i] = -32766;
		}
		else {
			data[i] = (short)res;
		}
	}
}

void Equalizer::JoinSource(vector<shared_ptr<Converter>> converterVec, vector<string> argv) {
	if (converterVec.size() != 1) {
		throw SoundProcessorException("wrong equalizer input arguments count, need 1");
	}

	source = converterVec[0];

	if (argv.size() != 5) {
		string out = "";
		for (auto s : argv) {
			out += s;
		}
		throw SoundProcessorException("wrong equalizer arguments count " + out);
	}

	for (int i = 0; i < 5; i++) {
		if (!StringUtilities::IsNumber(argv[i])) {
			throw SoundProcessorException(argv[i] + " is not integer");
		}
	}

	startInterval = stoi(argv[0]) * 44100;
	endInterval = stoi(argv[1]) * 44100;

	startEqualize = stoi(argv[2]);
	endEqualize = stoi(argv[3]);

	percent—hange = stoi(argv[4]);
}

string Equalizer::Help() {
	return string("equalizer help");
}
