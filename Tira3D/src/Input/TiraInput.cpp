#include "TiraInput.h"

void TiraInput::RecordInput(TiraKey key, tiraInputCallback function, TiraKeyPressType pressType)
{
	RecordedTiraInputs record;
	record.key = key;
	record.triggertype = pressType;
	record.callbackFunction = function;
	inputs.push_back(record);
}

void TiraInput::StopRecordingInput(TiraKey key, TiraKeyPressType pressType)
{
}

std::vector<RecordedTiraInputs>& TiraInput::GetExistingInputs()
{
	return inputs;
}
