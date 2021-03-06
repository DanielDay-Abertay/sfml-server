#include "CustomPacket.h"
#include "Server.h"

CustomPacket::CustomPacket()
{
}


CustomPacket::~CustomPacket()
{
}

//fills the packet with the connection request info
bool CustomPacket::fillPacket(playerInfo &info, sf::Packet& packet)
{
	packet.clear();
	if (packet << info.connectRequest << info.connectAccepted << info.timeStamp << info.timeOkay << info.timeSent << info.ID << info.seed << info.latency)
	{
		return true;
	}
	return false;
}
//fills the playerinfo packet
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
	//std::cout << packet.getDataSize() << std::endl;

	return true;
}
//checks that the content os okay of conenctino request 
bool CustomPacket::checkPacket(sf::Packet &packet, playerInfo *info)
{
	if (packet >> info->connectRequest >> info->connectAccepted >> info->timeStamp >> info->timeOkay >> info->timeSent >> info->ID >> info->seed >> info->latency)
	{
		return true;
	}
	return false;
}
//checks the content of the incoming player pos
bool CustomPacket::checkPacket(sf::Packet & packet, playerPos* pos)
{
	if (packet >> pos->timeStamp >> pos->xPos >> pos->yPos >>pos->ID)
	{
		packet.clear();
		return true;
	}
	return false;
}

//operater over writers for packets
sf::Packet& operator <<(sf::Packet& packet, const playerInfo& info)
{
	return packet << info.connectRequest << info.connectAccepted << info.timeStamp << info.timeOkay << info.timeSent << info.ID << info.seed << info.latency;
}

sf::Packet& operator >>(sf::Packet& packet, playerInfo& info)
{
	return packet >> info.connectRequest >> info.connectAccepted >> info.timeStamp >> info.timeOkay >> info.timeSent >> info.ID >> info.seed >> info.latency;
}


sf::Packet& operator <<(sf::Packet& packet, const playerPos& pos)
{
	return packet << pos.timeStamp << pos.xPos << pos.yPos << pos.ID;
}

sf::Packet& operator >> (sf::Packet& packet, playerPos& pos)
{
	return packet >> pos.timeStamp >> pos.xPos >> pos.yPos >> pos.ID;
}