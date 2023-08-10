#include "TiraInput.h"
#include <iostream>

TiraInput::TiraInput()
{
	inputs = std::vector<RecordedTiraInputs>();
	inputs.size();
}

void TiraInput::RecordInput(TiraKey key, std::function<void()> function, TiraKeyPressType pressType)
{
	try {
		RecordedTiraInputs record;
		record.key = key;
		record.triggertype = pressType;
		record.boundfunction = function;
		inputs.push_back(record);
	}
	catch (std::exception ex) {
		std::cout << "ohno " << ex.what() << std::endl;
	}
}

void TiraInput::StopRecordingInput(TiraKey key, TiraKeyPressType pressType)
{
}

std::vector<RecordedTiraInputs>& TiraInput::GetExistingInputs()
{
	return inputs;
}
