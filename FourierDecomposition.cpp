#include "FourierDecomposition.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

void FourierDecomposition::DoDecompose(
	short* data, 
	long int length, 
	int decompositionLength)
{
	double baseFrequency = 2 * M_PI / length;
	
	for (int i = 0; i < decompositionLength; i++) {
		double cosCoef = 0;
		double sinCoef = 0;
		for (int j = 0; j < length; j++) {
			cosCoef += data[j] * cos(j * i * baseFrequency);
			sinCoef += data[j] * sin(j * i * baseFrequency);
		}
		cosCoef *= 2;
		sinCoef *= 2;
		cosCoef /= length;
		sinCoef /= length;
		double x = 2;
		cos—oefficient.push_back(cosCoef);
		sinCoefficient.push_back(sinCoef);
	}
}

const vector<double>& FourierDecomposition::GetSinVec() {
	return sinCoefficient;
}

const vector<double>& FourierDecomposition::GetCosVec() {
	return cos—oefficient;
}

