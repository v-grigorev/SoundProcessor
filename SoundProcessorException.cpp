#include "SoundProcessorException.h"

SoundProcessorException::SoundProcessorException(const string& msg) {
	message = msg;
}

SoundProcessorException::SoundProcessorException(const char* msg) : message(msg) {
}

SoundProcessorException::SoundProcessorException(const char* msg, int err) : message(msg) {
	codeError = err;
}

int SoundProcessorException::GetCoderror() const {
	return codeError;
}

const char* SoundProcessorException::what() const {
	return message.data();
}
