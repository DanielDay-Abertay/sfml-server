#pragma once
#include <SFML/Network.hpp>
struct playerInfo;
struct playerPos;
struct otherPlayerInfo;

class CustomPacket
{
public:
	CustomPacket();
	~CustomPacket();
	bool fillPacket(playerInfo &info, sf::Packet& packet);
	bool checkPacket(sf::Packet& packet, playerInfo *info);
	bool checkPacket(sf::Packet& packet, playerPos *pos);
	bool fillPacket(otherPlayerInfo &other, sf::Packet& packet);
};

