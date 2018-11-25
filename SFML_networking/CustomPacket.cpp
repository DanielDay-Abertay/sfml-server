#include "CustomPacket.h"
#include "Server.h"

CustomPacket::CustomPacket()
{
}


CustomPacket::~CustomPacket()
{
}

bool CustomPacket::fillPacket(playerInfo &info, sf::Packet& packet)
{
	packet.clear();
	if (packet << info.connectRequest << info.connectAccepted << info.timeStamp << info.timeOkay << info.timeSent << info.ID << info.seed << info.padding)
	{
		std::cout << packet.getDataSize() << std::endl;
		return true;
	}
	return false;
}
bool CustomPacket::fillPacket(otherPlayerInfo &other, sf::Packet& packet)
{
	packet.clear();
	other.size = other.networkPlayerPos.size();
	packet << other.size;	
	for (std::list<playerPos>::iterator it = other.networkPlayerPos.begin(); it != other.networkPlayerPos.end(); ++it)
	{
		packet << it->timeStamp << it->xPos << it->yPos << it->ID;
	}
	packet << other.padding;
	std::cout << packet.getDataSize() << std::endl;

	return true;
}

bool CustomPacket::checkPacket(sf::Packet &packet, playerInfo *info)
{
	if (packet >> info->connectRequest >> info->connectAccepted >> info->timeStamp >> info->timeOkay >> info->timeSent >> info->ID >> info->seed >> info->padding)
	{
		return true;
	}
	return false;
}
bool CustomPacket::checkPacket(sf::Packet & packet, playerPos* pos)
{
	if (packet >> pos->timeStamp >> pos->xPos >> pos->yPos)
	{
		packet.clear();
		return true;
	}
	return false;
}


sf::Packet& operator <<(sf::Packet& packet, const playerInfo& info)
{
	return packet << info.connectRequest << info.connectAccepted << info.timeStamp << info.timeOkay << info.timeSent << info.ID << info.seed << info.padding;
}

sf::Packet& operator >>(sf::Packet& packet, playerInfo& info)
{
	return packet >> info.connectRequest >> info.connectAccepted >> info.timeStamp >> info.timeOkay >> info.timeSent >> info.ID >> info.seed >> info.padding;
}


sf::Packet& operator <<(sf::Packet& packet, const playerPos& pos)
{
	return packet << pos.timeStamp << pos.xPos << pos.yPos << pos.ID;
}

sf::Packet& operator >> (sf::Packet& packet, playerPos& pos)
{
	return packet >> pos.timeStamp >> pos.xPos >> pos.yPos >> pos.ID;
}