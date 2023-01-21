#include "Mixer.h"
#include "SoundProcessorException.h"
#include "StringUtilities.h"

void Mixer::JoinSource(vector< shared_ptr<Converter> > converterVec, vector<string> argv) {
    if (converterVec.size() != 2) {
        throw SoundProcessorException("wrong mixer input arguments count, need 2");
    }
    mainSource = converterVec[0];
    additionalSource = converterVec[1];

    if (argv.size() == 0) {
        convertOffset = 0;
        return;
    }
    if (argv.size() != 1) {
        string out = "";
        for (auto s : argv) {
            out += s;
        }
        throw SoundProcessorException("wrong mixer arguments count " + out);
    }

    if (!StringUtilities::IsNumber(argv[0])) {
        throw SoundProcessorException(argv[0] + " is not integer");
    }

    convertOffset = stoi(argv[0]) * 44100;
}

string Mixer::Help() {
    return string("Mixer help");
}

short* Mixer::GetData(long int offset, long int length) {
    short* mainData = mainSource->GetData(offset, length);
    if (offset - convertOffset < 0 || additionalSourceIsEnded) {
        readCount = mainSource->GetNumberOfRead();
        return mainData;
    }

    short* additionalData = additionalSource->GetData(offset - convertOffset, length);

    long int mainReadCount = mainSource->GetNumberOfRead();
    long int additionalReadCount = additionalSource->GetNumberOfRead();

    readCount = min<long int>(mainReadCount, additionalReadCount);

    vector<short*> dataVec;
    dataVec.push_back(mainData);
    dataVec.push_back(additionalData);
    IntervalHandle(dataVec, offset, readCount, convertOffset, 10000000000);

    if (additionalReadCount != length) {
        readCount = mainReadCount;
        additionalSourceIsEnded = true;
    }

    return mainData;
}

void Mixer::SingleConvert(vector<short*> dataVec, long int length) {
    short* mainData = dataVec[0];
    short* additionalData = dataVec[1];

    for (int i = 0; i < readCount; i++) {
        int res = (int)mainData[i] + (int)additionalData[i];
        res *= 0.9;
        if (res > 32766) {
            mainData[i] = 32766;
        }
        else if (res < -32766) {
            mainData[i] = -32766;
        }
        else {
            mainData[i] = (short)res;
        }
    }
}

