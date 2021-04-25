#include "Unused1D.h"
#include "StringHelper.h"

Unused1D::Unused1D(ZRoom* nZRoom, const std::vector<uint8_t>& rawData, uint32_t rawDataIndex)
	: ZRoomCommand(nZRoom, rawData, rawDataIndex)
{
}

std::string Unused1D::GetBodySourceCode() const
{
	return StringHelper::Sprintf("{ %s, 0x00, 0x00 }", GetCommandHex().c_str());
}

std::string Unused1D::GetCommandCName() const
{
	return "SCmdBase";
}

RoomCommand Unused1D::GetRoomCommand() const
{
	return RoomCommand::Unused1D;
}
