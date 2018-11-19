#include "Server.h"
#include <iostream>
using namespace std;
Server::Server()
{
	socket.setBlocking(false);
	timeStamp = clock.getElapsedTime().asMilliseconds();
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
	unsigned short port = 4444;
	// Wait for a message
	char in[128];
	std::size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;
	if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
		return;
	std::cout << "Message received from client " << sender << ": \"" << in << "\"" << std::endl;

	// Send an answer to the client
	const char out[] = "Hi, I'm the server";
	if (socket.send(out, sizeof(out), sender, senderPort) != sf::Socket::Done)
		return;
	std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;

	timeStamp = getTimeStamp();
	if (socket.send(&timeStamp, sizeof(timeStamp), sender, senderPort) != sf::Socket::Done)
	{
		std::cout << "time stamp not sent" << std::endl;
	}
	std::cout << "time stamp sent to the client: \"" << timeStamp << "\"" << std::endl;
	
	
	
}

sf::Uint32 Server::getTimeStamp()
{
	return clock.getElapsedTime().asMilliseconds();


}

