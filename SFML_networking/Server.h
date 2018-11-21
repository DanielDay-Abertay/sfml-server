#pragma once
#include <SFML\Network.hpp>
#include "CustomPacket.h"
#include <vector>

struct playerInfo
{
	bool connectRequest = false;
	bool connectAccepted = false;
	sf::Uint32 timeStamp = NULL;
	bool timeOkay = false;
	bool timeSent = false;
	int ID;
};

struct playerPos
{
	sf::Uint32 timeStamp = NULL;
	float xPos;
	float yPos;
	int ID;
};

class Server
{
public:
	Server();
	~Server();
	void udpBind();
	void listener();
	void confirmTimeStamp();
	sf::Uint32 getTimeStamp();


	bool sendPacket(sf::Packet packet);
	bool receivePacket();

	std::vector<playerPos> getPos() { return playerPosVec; }


protected:

	sf::TcpListener listenerSoc;
	sf::UdpSocket socket;
	sf::Int32 timeStamp;
	sf::Clock clock;
	
	CustomPacket pack;
	std::vector<playerInfo> playerInfoVec;
	std::vector<playerPos> playerPosVec;
	playerInfo info;
	playerPos pos;


	sf::Packet sentPacket;
	sf::Packet receivedPacket;

	unsigned short port;
	sf::IpAddress cliant;

	bool once = false;

	int count;

	int idCount;
};

