#pragma once
#include <SFML\Network.hpp>
#include "CustomPacket.h"
#include <vector>
#include <list>

struct playerInfo
{
	bool connectRequest = false;
	bool connectAccepted = false;
	sf::Uint32 timeStamp;
	bool timeOkay = false;
	bool timeSent = false;
	int ID;
	int seed;
	int latency;
};

struct playerPos
{
	sf::Uint32 timeStamp = NULL;
	float xPos;
	float yPos;
	int ID;
};
struct otherPlayerInfo
{
	int size;
	std::list<playerPos> networkPlayerPos;
	int padding;
};

struct setUp
{
	sf::IpAddress ip;
	int id;
	bool finishedSetUp = false;
	sf::Int32 latency;
	int stage;
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
	sf::Uint32 getTime() { return clock.getElapsedTime().asMilliseconds(); }


	bool sendPacket(sf::Packet packet, sf::IpAddress ip);
	bool receivePacket();

	std::vector<playerPos>* getPos();
	void resetInfo();

	void sendInfo();

	int getSeed() { return seed; }



	bool setUpStep1();
	bool setUpStep2();
	bool setUpStep3();


protected:

	sf::TcpListener listenerSoc;
	sf::UdpSocket socket;
	sf::Int32 timeStamp;
	sf::Clock clock;
	
	CustomPacket pack;
	std::vector<playerInfo> playerInfoVec;
	std::vector<playerPos> playerPosVec;
	std::vector<playerPos> playerPosVec1;
	std::vector<playerPos> playerPosVec2;
	playerInfo info;
	playerPos pos;


	sf::Packet sentPacket;
	sf::Packet receivedPacket;

	unsigned short port;
	sf::IpAddress cliant;

	bool once = false;

	int count;

	int idCount;

	otherPlayerInfo other;

	std::vector<setUp> connectedVec;

	int seed;
};

