#include "SetCollisionHeader.h"

#include "BitConverter.h"
#include "StringHelper.h"
#include "Globals.h"
#include "ZFile.h"
#include "ZRoom/ZRoom.h"

SetCollisionHeader::SetCollisionHeader(ZFile* nParent) : ZRoomCommand(nParent)
{
}

void SetCollisionHeader::ParseRawData()
{
	ZRoomCommand::ParseRawData();

	collisionHeader = new ZCollisionHeader(parent);
	collisionHeader->SetRawData(parent->GetRawData());
	collisionHeader->SetRawDataIndex(segmentOffset);
	collisionHeader->SetName(
		StringHelper::Sprintf("%sCollisionHeader_%06X", parent->GetName().c_str(), segmentOffset));
	collisionHeader->ParseRawData();
	parent->AddResource(collisionHeader);
}

void SetCollisionHeader::DeclareReferences(const std::string& prefix)
{
	collisionHeader->DeclareVar(prefix, "");
}

std::string SetCollisionHeader::GetBodySourceCode() const
{
	std::string listName;
	Globals::Instance->GetSegmentedPtrName(cmdArg2, parent, listName);
	return StringHelper::Sprintf("SCENE_CMD_COL_HEADER(%s)", listName.c_str());
}

std::string SetCollisionHeader::GetCommandCName() const
{
	return "SCmdColHeader";
}

RoomCommand SetCollisionHeader::GetRoomCommand() const
{
	return RoomCommand::SetCollisionHeader;
}
