#pragma once
#include <SFML\Network.hpp>
class Server
{
public:
	Server();
	~Server();
	void listener();
	void udpBind();


protected:

	sf::TcpListener listenerSoc;
	sf::UdpSocket socket;
	
};

