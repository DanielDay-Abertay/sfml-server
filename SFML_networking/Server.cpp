#include "Server.h"
#include <iostream>
using namespace std;
Server::Server()
{
	//set up inital server info
	socket.setBlocking(false);
	timeStamp = clock.getElapsedTime().asMilliseconds();
	port = 4444;
	seed = time(NULL);
	std::cout << "seed = " << seed << endl;

}

Server::~Server()
{
}
//bind the port, to hard coded value 4444
void Server::udpBind()
{
	unsigned short port = 4444;

	if (socket.bind(port) != sf::Socket::Done)
	{
		cout << "failed to bind" << endl;
		return;
	}
	std::cout << "Server is listening to port " << port << ", waiting for a message... " << std::endl;
}
//all incoming traffic comes through here
void Server::listener()
{
	if (!receivePacket())
	{
		return;
	}

	//if the player has not finished setup
	if (!connectedVec.back().finishedSetUp)
	{
		//check which stage it is at and take it to the appropiate function
		if (info.connectRequest && !info.connectAccepted)
		{
			setUpStep1();

		}
		if (info.connectAccepted && !info.timeSent)
		{

			setUpStep2();
			return;
		}

		if (playerInfoVec[info.ID].timeSent && !playerInfoVec[info.ID].timeOkay)
		{
			if (setUpStep3())
			{
				return;
			}
		}
	}
}

sf::Uint32 Server::getTimeStamp()
{
	return clock.getElapsedTime().asMilliseconds();
}

bool Server::sendPacket(sf::Packet packet, sf::IpAddress ip)
{
	port = 4441; //i have no idea why it forgets the port... i dont think it gets re-set... need to ask
	if (socket.send(packet, ip, port) != sf::Socket::Done)
	{
		return false;
	}
	return true;
}
//all incoming traffic comes through here
bool Server::receivePacket()
{
	//local vairable to store the ipadress my be used to refrence later 
	sf::IpAddress ipaddress;
	if (socket.receive(receivedPacket, ipaddress, port) != sf::Socket::Done)
	{
		return false;
	}
	

	//packets are sorted by size.... not a great idea for security
	if (receivedPacket.getDataSize() == 16)
	{
		playerPos newPos;
		//checks the validity of the packet
		//this checks if this is incoming player info
		if (pack.checkPacket(receivedPacket, &newPos))
		{
			//stores last 3 positoins. Would be used for server side prediction/ security checks/cheating. Not been implemented in server side
			playerPosVec2[newPos.ID] = playerPosVec1[newPos.ID];
			playerPosVec1[newPos.ID] = playerPosVec[newPos.ID];
			playerPosVec[newPos.ID] = newPos;
			newPos.ID = NULL;
			return true;
		}
	}
	//checks if incoming packets are connetion requests
	else if (receivedPacket.getDataSize() == 20)
	{
		if (pack.checkPacket(receivedPacket, &info))
		{
			//loops through the connected cliant vector and checks if there ip is already stored. 
			//if it is already stored no need to do anything, it will be handles somewhere else
			for (int i = 0; i < connectedVec.size(); i++)
			{
				if (ipaddress == connectedVec[i].ip)
				{
					return true;
				}
			}
			//if this is the first packet of the handshake set up there info
			sf::IpAddress test = ipaddress;
			setUp tempSetUp;
			tempSetUp.ip = ipaddress;
			tempSetUp.id = connectedVec.size();
			tempSetUp.finishedSetUp = false;
			connectedVec.push_back(tempSetUp);
			cout << "connected vec added" << endl;
			return true;
		}
	}

	return false;
}
//function packs all player positons into a a packet and sends to all cliants connected
void Server::sendInfo()
{
	//clears the existing info in list
	other.networkPlayerPos.clear();
	//loops over stored data and puts back into list
	for (int i = 0; i < playerPosVec.size(); i++)
	{
		//only sen info of the players who have completed setup
		if (connectedVec[i].finishedSetUp)
		{
			if (playerPosVec[i].timeStamp != NULL)
			{
				other.networkPlayerPos.push_back(playerPosVec[i]);
			}
		}
	}
	//send info to be put in packet
	if (!pack.fillPacket(other, sentPacket))
	{
		cout << "oh dear" << endl;
		return;
	}
	//sends to all cliants
	for (int i = 0; i < connectedVec.size(); i++)
	{
		if (connectedVec[i].finishedSetUp)
		{
			if (!sendPacket(sentPacket, connectedVec[i].ip))
			{
				return;
			}
		}
	}
}
//inital connection step
bool Server::setUpStep1()
{
	//set inital info to send back to confurm connection
	cout << "acceppted connection" << endl;
	info.connectAccepted = true;
	info.ID = playerInfoVec.size();
	info.seed = seed;
	playerInfoVec.push_back(info);

	//fill the packet and check that it went ok
	if (!pack.fillPacket(info, sentPacket))
	{
		cout << "failed to fill" << endl;
		return false;
	}
	//send packet and see if its ok
	if (!sendPacket(sentPacket, connectedVec.back().ip))
	{
		cout << "failed to send" << endl;
		return false;
	}
	return true;
}
//second step in connection
bool Server::setUpStep2()
{
	// setting up more info to establish connection - sending server time to establish latecny
	playerInfoVec[info.ID].timeStamp = getTimeStamp();
	playerInfoVec[info.ID].timeSent = true;
	if (!pack.fillPacket(playerInfoVec[info.ID], sentPacket))
	{
		cout << "something went wrong" << endl;
		playerInfoVec[info.ID].timeSent = false;
		return false;
	}

	if (!sendPacket(sentPacket, connectedVec[info.ID].ip))
	{
		cout << "failed to send" << endl;
		return false;;
	}
	cout << "sent message" << endl;
	cout << "time stamp =" << info.timeStamp << endl;
	return true;
}
//final connection step
bool Server::setUpStep3()
{
	cout << "time stamp sent back" << endl;
	playerInfoVec[info.ID].latency = (getTime() - playerInfoVec[info.ID].timeStamp) / 2;
	cout << "the latency between cliant and server is " << playerInfoVec[info.ID].latency << endl;
	playerInfoVec[info.ID].timeOkay = true;
	playerInfoVec[info.ID].timeStamp = getTime();

	if (!pack.fillPacket(playerInfoVec[info.ID], sentPacket))
	{
		cout << "something went wrong" << endl;
		return false;
	}

	if (!sendPacket(sentPacket, connectedVec[info.ID].ip))
	{
		cout << "failed to send" << endl;
		return false;
	}

	//once connected add give it a position in the vector of player position 
	cout << "connection established" << endl;
	playerPos pos;
	pos.ID = info.ID;
	playerPosVec.push_back(pos);
	playerPosVec1.push_back(pos);
	playerPosVec2.push_back(pos);
	cout << "position added" << endl;
	connectedVec[info.ID].finishedSetUp = true;

	return true;
}

//used to render to server 
std::vector<playerPos>* Server::getPos()
{
	return &playerPosVec;
}