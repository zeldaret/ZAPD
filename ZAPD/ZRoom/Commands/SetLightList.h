#pragma once

#include <string>

#include "../ZRoom.h"
#include "../ZRoomCommand.h"
#include "ZFile.h"

class LightInfo
{
public:
	LightInfo(const std::vector<uint8_t>& rawData, int rawDataIndex);

	std::string GetBodySourceCode() const;

	std::string GetSourceTypeName() const;
	size_t GetRawDataSize() const;

protected:
	uint8_t type;
	int16_t x, y, z;
	uint8_t r, g, b;
	uint8_t drawGlow;
	int16_t radius;
};

class SetLightList : public ZRoomCommand
{
public:
	SetLightList(ZRoom* nZRoom, const std::vector<uint8_t>& rawData, int rawDataIndex);

	void ParseRawData() override;
	void DeclareReferences(const std::string& prefix) override;

	std::string GetBodySourceCode() const override;

	RoomCommand GetRoomCommand() const override;
	std::string GetCommandCName() const override;

private:
	uint8_t code;
	uint8_t numLights;
	std::vector<LightInfo> lights;
};
