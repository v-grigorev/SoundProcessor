#pragma once
#include <vector>
#include <utility>

using namespace std;

class FourierDecomposition {
public:
	void DoDecompose(short* data, long int length, int decompositionLength);
	const vector<double>& GetSinVec();
	const vector<double>& GetCosVec();
private:
	vector<double> cos—oefficient;
	vector<double> sinCoefficient;
};

