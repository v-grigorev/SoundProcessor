#include "ConverterFactory.h"
#include "SoundProcessorException.h"
#include "Mute.h"
#include "Mixer.h"
#include "Equalizer.h"
#include <iostream>

ConverterFactory::ConverterFactory() {
    factoryMap["PCMReader"] = make_shared<PCMReader>();
    factoryMap["mix"] = make_shared<Mixer>();
}

shared_ptr<Converter> ConverterFactory::GetConverter(const string& converterName) {
    if (converterName == "mix") {
        return make_shared<Mixer>();
    }
    if (converterName == "mute") {
        return make_shared<Mute>();
    }
    if (converterName == "equalize") {
        return make_shared<Equalizer>();
    }
    throw SoundProcessorException("command not found: " + converterName);
}

void ConverterFactory::Help() {
    cout << Mixer().Help() << endl;
    cout << "--------------" << endl;
    cout << Mute().Help() << endl;
    cout << "--------------" << endl;
    cout << Equalizer().Help() << endl;
    cout << "--------------" << endl;
}
