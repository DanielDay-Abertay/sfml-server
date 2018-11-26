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

	if (info.connectRequest == true && info.connectAccepted == false)
	{
		//idCount++;
		cout << "acceppted connection"<< endl;
		info.connectAccepted = true;
		info.ID = idCount;
		info.seed = seed;
		playerInfoVec.push_back(info);
		if (!pack.fillPacket(info, sentPacket))
		{
			return;
		}

		if (!sendPacket(sentPacket, ipVec.back()))
		{
			cout << "failed to send" << endl;
		}
		//return;
	}
	
	
	if (info.connectAccepted == true && info.connectRequest == true && info.timeSent == false)
	{
		sf::Packet packetnew;
		cout << "sending timestamp" << endl;
		
		playerInfoVec[info.ID].timeStamp = getTimeStamp();
		playerInfoVec[info.ID].timeSent = true;
		if (!pack.fillPacket(playerInfoVec[info.ID], sentPacket))
		{
			
			cout << "something went wrong" << endl;
		}

		if (!sendPacket(sentPacket, ipVec.back()))
		{
			cout << "failed to send" << endl;
		}
		cout << "time stamp =" << getTimeStamp() << endl;
 		return;
	}

	if (info.timeSent && info.timeOkay == false)
	{
		cout << "time stamp sent back" << endl;
		if (info.timeStamp < getTimeStamp() + 100 )
		{
			playerInfoVec[info.ID].timeOkay = true;
			if (!pack.fillPacket(playerInfoVec[info.ID], sentPacket))
			{

				cout << "something went wrong" << endl;
			}

			if (!sendPacket(sentPacket, ipVec.back()))
			{
				cout << "failed to send" << endl;
			}
			cout << "all good" << endl;
			playerPos pos;
			pos.ID = info.ID;
			playerPosVec.push_back(pos);
			cout << "added" << endl;
			info.timeOkay = true; //will need to change 

			resetInfo();
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
	if (socket.receive(receivedPacket, cliant, port) != sf::Socket::Done)
	{
		return false;
	}
	//cout << cliant << endl;


	if (receivedPacket.getDataSize() == 16)
	{
		if (pack.checkPacket(receivedPacket, &pos))
		{
			count++;
			if (count = 20)
			{
				//cout << "server time is " << getTimeStamp() << " packet sent at " << pos.timeStamp << " local time" << endl;
				count = 0;
			}
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
			for (int i = 0; i < ipVec.size(); i++)
			{
				if (cliant == ipVec[i])
				{
					return true;
				}

			}
			ipVec.push_back(cliant);
			return true;
		}
	}
	

	return false;

}

void Server::sendInfo()
{
	other.networkPlayerPos.clear();
	for (auto it : playerPosVec)
	{
		if (it.timeStamp != NULL)
		{
			other.networkPlayerPos.push_back(it);
		}
		
	}

	if (!pack.fillPacket(other, sentPacket))
	{
		cout << "oh dear" << endl;
		return;
	}
	for (int i = 0; i < ipVec.size(); i++)
	{
	
		if (!sendPacket(sentPacket, ipVec[i]))
		{
			return;

		}
	}
	
}
std::vector<playerPos>* Server::getPos()
{
	return &playerPosVec;
}

void Server::resetInfo()
{
	info.connectRequest = false;
	info.connectAccepted = false;
	info.timeStamp = NULL;
	info.timeOkay = false;
	info.timeSent = false;
	info.ID = NULL;
	info.seed = NULL;
	info.padding = NULL;
}

