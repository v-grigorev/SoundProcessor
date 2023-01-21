#include "Mute.h"
#include "SoundProcessorException.h"
#include "StringUtilities.h"
#include <memory>

short* Mute::GetData(long int offset, long int length) {
    short* data = source->GetData(offset, length);
    readCount = source->GetNumberOfRead();

    vector<short*> dataVec;
    dataVec.push_back(data);

    IntervalHandle(dataVec, offset, readCount, startMute, endMute);

    return data;
}

void Mute::SingleConvert(vector<short*> dataVec, long int lenght) {
    memset(dataVec[0], 0, lenght * sizeof(short));
}

void Mute::JoinSource(vector<shared_ptr<Converter>> converterVec, vector<string> argv) {
    if (converterVec.size() != 1) {
        throw SoundProcessorException("wrong mute input arguments count, need 1");
    }

    source = converterVec[0];

    if (argv.size() != 2) {
        string out = "";
        for (auto s : argv) {
            out += s;
        }
        throw SoundProcessorException("wrong mute arguments count " + out);
    }

    if (!StringUtilities::IsNumber(argv[0])) {
        throw SoundProcessorException(argv[0] + " is not integer");
    }

    if (!StringUtilities::IsNumber(argv[0])) {
        throw SoundProcessorException(argv[1] + " is not integer");
    }

    startMute = stoi(argv[0]) * 44100;
    endMute = stoi(argv[1]) * 44100;
}

string Mute::Help() {
    return string("Mute help");
}
