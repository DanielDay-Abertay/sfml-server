#include "Server.h"
#include <iostream>
using namespace std;
Server::Server()
{
	socket.setBlocking(false);
	timeStamp = clock.getElapsedTime().asMilliseconds();
	port = 4444;
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
		cout << "acceppted connection"<< endl;
		info.connectAccepted = true;
		if (!pack.fillPacket(info, sentPacket))
		{
			return;
		}

		if (!sendPacket(sentPacket))
		{
			cout << "failed to send" << endl;
		}
		//return;
	}
	
	
	if (info.connectAccepted == true && info.connectRequest == true && info.timeSent == false)
	{
		sf::Packet packetnew;
		
		info.timeStamp = getTimeStamp();
		info.timeSent = true;
		if (!pack.fillPacket(info, sentPacket))
		{
			
			cout << "something went wrong" << endl;
		}

		if (!sendPacket(sentPacket))
		{
			cout << "failed to send" << endl;
		}
		cout << "time stmap =" << info.timeStamp << endl;
		return;
	}

	if (info.timeSent)
	{
		if (info.timeStamp < getTimeStamp() + 100 )
		{
			info.timeOkay = true;
			if (!pack.fillPacket(info, sentPacket))
			{

				cout << "something went wrong" << endl;
			}

			if (!sendPacket(sentPacket))
			{
				cout << "failed to send" << endl;
			}
			cout << "all good" << endl;
		}
	}


	
	
}

sf::Uint32 Server::getTimeStamp()
{
	return clock.getElapsedTime().asMilliseconds();


}

bool Server::sendPacket(sf::Packet packet)
{

	if (socket.send(packet, cliant, port) != sf::Socket::Done)
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
	cout << receivedPacket.getDataSize() << endl;
	if (receivedPacket.getDataSize() == 12)
	{
		if (pack.checkPacket(receivedPacket, &pos))
		{
			cout << pos.xPos << " " << pos.yPos << endl;
			return true;
		}
	}
	else if (receivedPacket.getDataSize() == 8)
	{
		if (pack.checkPacket(receivedPacket, &info))
		{
			
			return true;
		}
	}
	

	return false;

}