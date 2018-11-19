#include "Server.h"
#include <iostream>
using namespace std;
Server::Server()
{
}

Server::~Server()
{
}


void Server::udpBind()
{
	if (socket.bind(4444) != sf::Socket::Done)
	{
		cout << "failed to bind" << endl;
	}



}
void Server::listener()
{

	if (listenerSoc.listen(4444) != sf::Socket::Done)
	{
		cout << "Failed to bind listenerSoc on " << listenerSoc.getLocalPort() << endl;
		// error...
	}
	else
	{
		cout << "new cliant connecting" << endl;

		sf::TcpSocket cliant;
		if (listenerSoc.accept(cliant) != sf::Socket::Done)
		{
			cout << "failled to connect" << endl;
		}
		else
		{

			const char out[] = "Hi, I'm the server";
			if (cliant.send(out, sizeof(out)) != sf::Socket::Done)
			{
				cout << "failed to send message" << endl;
			}
			
			else
			{
				std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;
			}
			
			
		}

	}

}
