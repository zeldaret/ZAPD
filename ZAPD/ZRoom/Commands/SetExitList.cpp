#include "SetExitList.h"
#include "../../BitConverter.h"
#include "../../StringHelper.h"
#include "../../ZFile.h"
#include "../ZRoom.h"

using namespace std;

SetExitList::SetExitList(ZRoom* nZRoom, const std::vector<uint8_t>& rawData, int rawDataIndex)
	: ZRoomCommand(nZRoom, rawData, rawDataIndex)
{
	if (segmentOffset != 0)
		parent->AddDeclarationPlaceholder(segmentOffset);
}

void SetExitList::ParseRawDataLate()
{
	// Parse Entrances and Generate Declaration
	int numEntrances = zRoom->GetDeclarationSizeFromNeighbor(segmentOffset) / 2;
	uint32_t currentPtr = segmentOffset;

	for (int i = 0; i < numEntrances; i++)
	{
		uint16_t exit = BitConverter::ToUInt16BE(rawData, currentPtr);
		exits.push_back(exit);

		currentPtr += 2;
	}
}

void SetExitList::DeclareReferencesLate(const std::string& prefix)
{
	if (!exits.empty()) {
		std::string declaration = "";

		for (size_t i = 0; i < exits.size(); i++)
		{
			declaration += StringHelper::Sprintf("    0x%04X,", exits.at(i));
			if (i + 1 < exits.size())
				declaration += "\n";
		}

		parent->AddDeclarationArray(
			segmentOffset, DeclarationAlignment::Align4, exits.size() * 2, "u16",
			StringHelper::Sprintf("%sExitList0x%06X", zRoom->GetName().c_str(), segmentOffset),
			exits.size(), declaration);
	}
}

std::string SetExitList::GetBodySourceCode()
{
	std::string listName = parent->GetDeclarationPtrName(segmentOffset);
	return StringHelper::Sprintf("SCENE_CMD_EXIT_LIST(%s)", listName.c_str());
}

string SetExitList::GetCommandCName()
{
	return "SCmdExitList";
}

RoomCommand SetExitList::GetRoomCommand()
{
	return RoomCommand::SetExitList;
}
