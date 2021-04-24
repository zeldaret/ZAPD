#pragma once

#include "../ZRoomCommand.h"

class SetWorldMapVisited : public ZRoomCommand
{
public:
	SetWorldMapVisited(ZRoom* nZRoom, const std::vector<uint8_t>& rawData, int rawDataIndex);

	std::string GetBodySourceCode() const override;

	RoomCommand GetRoomCommand() const override;
	std::string GetCommandCName() const override;
};
