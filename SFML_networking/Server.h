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
	sf::Uint32 getTimeStamp();
	sf::Uint32 getTime() { return clock.getElapsedTime().asMilliseconds(); }


	bool sendPacket(sf::Packet packet, sf::IpAddress ip);
	bool receivePacket();

	std::vector<playerPos>* getPos();

	void sendInfo();

	int getSeed() { return seed; }

	//conbnection functions
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

	//stores players positoin that come in not used for anything
	std::vector<playerPos> playerPosVec;
	std::vector<playerPos> playerPosVec1;
	std::vector<playerPos> playerPosVec2;


	//used as temp storage
	playerInfo info;
	playerPos pos;
	otherPlayerInfo other;
	std::vector<setUp> connectedVec;

	sf::Packet sentPacket;
	sf::Packet receivedPacket;

	unsigned short port;	

	int seed;
};

