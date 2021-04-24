#include "SetSkyboxModifier.h"
#include "../../StringHelper.h"

using namespace std;

SetSkyboxModifier::SetSkyboxModifier(ZRoom* nZRoom, const std::vector<uint8_t>& rawData, int rawDataIndex)
	: ZRoomCommand(nZRoom, rawData, rawDataIndex)
{
	disableSky = rawData.at(rawDataIndex + 0x04);
	disableSunMoon = rawData.at(rawDataIndex + 0x05);
}

std::string SetSkyboxModifier::GetBodySourceCode() const
{
	return StringHelper::Sprintf("SCENE_CMD_SKYBOX_DISABLES(0x%02X, 0x%02X)", disableSky, disableSunMoon);
}

string SetSkyboxModifier::GetCommandCName() const
{
	return "SCmdSkyboxDisables";
}

RoomCommand SetSkyboxModifier::GetRoomCommand() const
{
	return RoomCommand::SetSkyboxModifier;
}
