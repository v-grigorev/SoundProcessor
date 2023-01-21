#include "Converter.h"

long int Converter::GetNumberOfRead() const {
    return readCount;
}

void Converter::IntervalHandle(
    vector<short*> dataVec,
    long int offset,
    long int length,
    long int startInterval,
    long int endInterval)
{
    long int lengthIntervalForHandle = 0;
    if (endInterval < offset) {
        return;
    }
    if (startInterval > offset + length) {
        return;
    }
    if (startInterval < offset) {
        if (endInterval > offset + length) {
            lengthIntervalForHandle = length;
        }
        else {
            lengthIntervalForHandle = endInterval - offset;
        }
    }
    else {

        for (int i = 0; i < dataVec.size(); i++) {
            dataVec[i] += startInterval - offset;
        }

        if (endInterval > offset + length) {
            lengthIntervalForHandle = offset + length - startInterval;
        }
        else {
            lengthIntervalForHandle = endInterval - startInterval;
        }
    }
    SingleConvert(dataVec, lengthIntervalForHandle);
}
