#include "Server.h"
#include <iostream>
using namespace std;
Server::Server()
{
	socket.setBlocking(false);
	timeStamp = clock.getElapsedTime().asMilliseconds();
	port = 4444;
	count = 0;
	idCount = 0;
	seed = time(0);
	std::cout << "seed = " << seed << endl;
}

Server::~Server()
{
}


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
void Server::confirmTimeStamp()
{
	std::size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;
	sf::Uint32 time;
	if (socket.receive(&time, sizeof(time), received, sender, senderPort) != sf::Socket::Done)
	{
		cout << "failed to reciev" << endl;
	}
	else
	{
		if (time + 200 > getTimeStamp())
		{
			cout << "respose to long" << endl;
		}
		else
		{
			cout << "time fine" << endl;
		}
	}

}
void Server::listener()
{
	if (!receivePacket())
	{
		return;
	}

	if (!connectedVec.back().finishedSetUp)
	{
		if (info.connectRequest && !info.connectAccepted)
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
				return;
			}
			//send packet and see if its ok
			if (!sendPacket(sentPacket, connectedVec.back().ip))
			{
				cout << "failed to send" << endl;
				return;
			}
			
		}
		if (info.connectAccepted && !info.timeSent)
		{
			
			//setting up more info to establish connection - sending server time to establish latecny
			playerInfoVec[info.ID].timeStamp = getTimeStamp();
			playerInfoVec[info.ID].timeSent = true;
			if (!pack.fillPacket(playerInfoVec[info.ID], sentPacket))
			{

				cout << "something went wrong" << endl;
				playerInfoVec[info.ID].timeSent = false;
			}

			if (!sendPacket(sentPacket, connectedVec[info.ID].ip))
			{
				cout << "failed to send" << endl;
				return;
			}
			cout << "sent message" << endl;
			cout << "time stamp =" << info.timeStamp << endl;
			return;
		}

		if (playerInfoVec[info.ID].timeSent && !playerInfoVec[info.ID].timeOkay)
		{
			cout << "time stamp sent back" << endl;
			cout << "the latency between cliant and server is " << getTime() - playerInfoVec[info.ID].timeStamp << endl;
			playerInfoVec[info.ID].timeOkay = true;

			if (!pack.fillPacket(playerInfoVec[info.ID], sentPacket))
			{

				cout << "something went wrong" << endl;
				return;
			}

			if (!sendPacket(sentPacket, connectedVec[info.ID].ip))
			{
				cout << "failed to send" << endl;
				return;
			}

			cout << "connection established" << endl;
			playerPos pos;
			pos.ID = info.ID;
			playerPosVec.push_back(pos);
			cout << "position added" << endl;
			connectedVec[info.ID].finishedSetUp = true;
			return;

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

bool Server::receivePacket()
{
	sf::IpAddress ipaddress;
	if (socket.receive(receivedPacket, ipaddress, port) != sf::Socket::Done)
	{
		return false;
	}
	//cout << cliant << endl;


	if (receivedPacket.getDataSize() == 16)
	{
		if (pack.checkPacket(receivedPacket, &pos))
		{
			playerPosVec[pos.ID] = pos;
			//
			return true;
		}
	}
	else if (receivedPacket.getDataSize() == 20)
	{
		if (pack.checkPacket(receivedPacket, &info))
		{
			cout << info.connectAccepted << " " << info.connectRequest << " " << info.ID << " " << info.timeOkay << " " << info.timeSent << endl;
			for (int i = 0; i < connectedVec.size(); i++)
			{
				if (info.ID == connectedVec[i].id)
				{
					return true;
				}

			}
			
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

void Server::sendInfo()
{
	other.networkPlayerPos.clear();
	for (int i = 0; i < playerPosVec.size(); i++)
	{
		if (connectedVec[i].finishedSetUp)
		{
			if (playerPosVec[i].timeStamp != NULL)
			{
				other.networkPlayerPos.push_back(playerPosVec[i]);
			}
		}
	}

	if (!pack.fillPacket(other, sentPacket))
	{
		cout << "oh dear" << endl;
		return;
	}
	for (int i = 0; i < connectedVec.size(); i++)
	{
	
		if (!sendPacket(sentPacket, connectedVec[i].ip))
		{
			return;

		}
	}
	
}
std::vector<playerPos>* Server::getPos()
{
	return &playerPosVec;
}


