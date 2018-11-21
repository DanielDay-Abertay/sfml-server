#pragma once
#include <SFML\Network.hpp>
#include "CustomPacket.h"

struct playerInfo
{
	bool connectRequest = false;
	bool connectAccepted = false;
	sf::Uint32 timeStamp = NULL;
	bool timeOkay = false;
	bool timeSent = false;
};

struct playerPos
{
	sf::Uint32 timeStamp = NULL;
	float xPos;
	float yPos;
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


protected:

	sf::TcpListener listenerSoc;
	sf::UdpSocket socket;
	sf::Int32 timeStamp;
	sf::Clock clock;
	
	CustomPacket pack;
	playerInfo info;
	playerPos pos;


	sf::Packet sentPacket;
	sf::Packet receivedPacket;

	unsigned short port;
	sf::IpAddress cliant;

	bool once = false;
};

