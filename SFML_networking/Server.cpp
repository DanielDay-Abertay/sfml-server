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
		playerInfoVec.push_back(info);
		if (!pack.fillPacket(info, sentPacket))
		{
			return;
		}

		if (!sendPacket(sentPacket, cliant))
		{
			cout << "failed to send" << endl;
		}
		//return;
	}
	
	
	if (info.connectAccepted == true && info.connectRequest == true && info.timeSent == false)
	{
		sf::Packet packetnew;
		
		
		playerInfoVec[info.ID].timeStamp = getTimeStamp();
		playerInfoVec[info.ID].timeSent = true;
		if (!pack.fillPacket(playerInfoVec[info.ID], sentPacket))
		{
			
			cout << "something went wrong" << endl;
		}

		if (!sendPacket(sentPacket, cliant))
		{
			cout << "failed to send" << endl;
		}
		cout << "time stamp =" << getTimeStamp() << endl;
		return;
	}

	if (info.timeSent && info.timeOkay == false)
	{
		if (info.timeStamp < getTimeStamp() + 100 )
		{
			playerInfoVec[info.ID].timeOkay = true;
			if (!pack.fillPacket(playerInfoVec[info.ID], sentPacket))
			{

				cout << "something went wrong" << endl;
			}

			if (!sendPacket(sentPacket, cliant))
			{
				cout << "failed to send" << endl;
			}
			cout << "all good" << endl;
			playerPos pos;
			pos.ID = info.ID;
			playerPosVec.push_back(pos);

		}
	}


	
	
}

sf::Uint32 Server::getTimeStamp()
{
	return clock.getElapsedTime().asMilliseconds();


}

bool Server::sendPacket(sf::Packet packet, sf::IpAddress ip)
{
	port = 4444; //i have no idea why it forgets the port... i dont think it gets re-set... need to ask
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
	//cout << receivedPacket.getDataSize() << endl;
	if (receivedPacket.getDataSize() == 16)
	{
		if (pack.checkPacket(receivedPacket, &pos))
		{
			count++;
			if (count = 20)
			{
				cout << "server time is " << getTimeStamp() << " packet sent at " << pos.timeStamp << " local time" << endl;
				count = 0;
			}
			playerPosVec[pos.ID] = pos;
			//
			return true;
		}
	}
	else if (receivedPacket.getDataSize() == 12)
	{
		if (pack.checkPacket(receivedPacket, &info))
		{
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
