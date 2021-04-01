#include "ZCutsceneMM.h"
#include "BitConverter.h"
#include "StringHelper.h"

using namespace std;

ZCutsceneMM::ZCutsceneMM(std::vector<uint8_t> nRawData, int rawDataIndex, int rawDataSize)
{
	rawData = std::move(nRawData);
	segmentOffset = rawDataIndex;

	numCommands = BitConverter::ToInt32BE(rawData, rawDataIndex + 0);
	commands = vector<CutsceneCommand*>();

	endFrame = BitConverter::ToInt32BE(rawData, rawDataIndex + 4);
	uint32_t currentPtr = rawDataIndex + 8;
	uint32_t lastData = 0;

	bool doContinue = true;

	while (doContinue)
	{
		do
		{
			lastData = BitConverter::ToInt32BE(rawData, currentPtr);
			data.push_back(lastData);
			currentPtr += 4;
		} while (lastData != 0xFFFFFFFF);

		doContinue = false;

		// It seems cutscenes are padded to be a multiple of 16 bytes, even though it isn't aligned as such
		// TODO check that these are 0
		while (((data.size() + 2) % 4) != 0)
		{
			lastData = BitConverter::ToInt32BE(rawData, currentPtr);
			if (lastData != 0)
			{
				doContinue = true;
				break;
			}
			data.push_back(lastData);
			currentPtr += 4;

		}
	}
}

ZCutsceneMM::~ZCutsceneMM()
{
	for (CutsceneCommand* cmd : commands)
		delete cmd;
}

string ZCutsceneMM::GetSourceOutputCode(const std::string& prefix)
{
	string output = "";
	size_t size = 0;
	int32_t curPtr = 0;

	// output += StringHelper::Sprintf("// SIZE = 0x%04X\n", GetRawDataSize());
	output += StringHelper::Sprintf("\tCS_BEGIN_CUTSCENE(%i, %i),\n", numCommands, endFrame);

	for (size_t i = 0; i < data.size(); i++)
	{
		output += StringHelper::Sprintf("\t0x%08X,", data[i]);
		if ((i % 4) == 3)
		    output += "\n";
	}

	//output += StringHelper::Sprintf("\tCS_END(),\n", commands.size(), endFrame);

	return output;
}

int ZCutsceneMM::GetRawDataSize()
{
	return 8 + data.size() * 4;
}

ZResourceType ZCutsceneMM::GetResourceType()
{
	return ZResourceType::Cutscene;
}