#pragma once

#include "ZRoom/ZRoomCommand.h"

class SetWind : public ZRoomCommand
{
public:
	SetWind(ZRoom* nZRoom, const std::vector<uint8_t>& rawData, uint32_t rawDataIndex);

	std::string GetBodySourceCode() const override;

	std::string GetCommandCName() const override;
	RoomCommand GetRoomCommand() const override;

private:
	uint8_t windWest;
	uint8_t windVertical;
	uint8_t windSouth;
	uint8_t clothFlappingStrength;
};
