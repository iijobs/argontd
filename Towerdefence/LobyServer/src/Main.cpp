/*
 * Main.cpp
 *
 *  Created on: Sep 27, 2009
 *      Author: arutha
 */

#include "NetworkSystem.h"
#include "Loby.h"
#include "RPC3.h"

#include "raknet/BitStream.h"
#include "raknet/MessageIdentifiers.h"
#include "raknet/RakSleep.h"
#include "raknet/NetworkIDObject.h"
#include "raknet/NetworkIDManager.h"
#include "raknet/GetTime.h"

static Loby loby;

void list ( Loby& loby ){
	loby = ::loby;
}

void go(){
	Packet *p;
	while (1)
	{
		for (p=NetworkSystem::getRakPeerInterface()->Receive(); p; NetworkSystem::getRakPeerInterface()->DeallocatePacket(p), p=NetworkSystem::getRakPeerInterface()->Receive())
		{
			switch (p->data[0])
			{
			case ID_DISCONNECTION_NOTIFICATION:
				std::cerr << "ID_DISCONNECTION_NOTIFICATION" << std::endl;
				break;
			case ID_ALREADY_CONNECTED:
				std::cerr << "ID_ALREADY_CONNECTED" << std::endl;
				break;
			case ID_CONNECTION_ATTEMPT_FAILED:
				std::cerr << "Connection attempt failed" << std::endl;
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				std::cerr << "ID_NO_FREE_INCOMING_CONNECTIONS" << std::endl;
				break;
			case ID_PONG:
				std::cerr << "ID_PONG" << std::endl;
				//rakPeer->Connect(p->systemAddress.ToString(false),p->systemAddress.port,0,0,0);
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				std::cerr << "ID_CONNECTION_REQUEST_ACCEPTED" << std::endl;
				break;
			case ID_NEW_INCOMING_CONNECTION:
			{
				std::cerr << "ID_NEW_INCOMING_CONNECTION" << std::endl;
				break;
			}
			case ID_RPC_REMOTE_ERROR:
				{
					// Recipient system returned an error
					switch (p->data[1])
					{
					case RakNet::RPC_ERROR_NETWORK_ID_MANAGER_UNAVAILABLE:
						std::cerr << "RPC_ERROR_NETWORK_ID_MANAGER_UNAVAILABLE" << std::endl;
						break;
					case RakNet::RPC_ERROR_OBJECT_DOES_NOT_EXIST:
						std::cerr << "RPC_ERROR_OBJECT_DOES_NOT_EXIST" << std::endl;
						break;
					case RakNet::RPC_ERROR_FUNCTION_INDEX_OUT_OF_RANGE:
						std::cerr << "RPC_ERROR_FUNCTION_INDEX_OUT_OF_RANGE" << std::endl;
						break;
					case RakNet::RPC_ERROR_FUNCTION_NOT_REGISTERED:
						std::cerr << "RPC_ERROR_FUNCTION_NOT_REGISTERED" << std::endl;
						break;
					case RakNet::RPC_ERROR_FUNCTION_NO_LONGER_REGISTERED:
						std::cerr << "RPC_ERROR_FUNCTION_NO_LONGER_REGISTERED" << std::endl;
						break;
					case RakNet::RPC_ERROR_CALLING_CPP_AS_C:
						std::cerr << "RPC_ERROR_CALLING_CPP_AS_C" << std::endl;
						break;
					case RakNet::RPC_ERROR_CALLING_C_AS_CPP:
						std::cerr << "RPC_ERROR_CALLING_C_AS_CPP" << std::endl;
						break;
					}
					std::cerr << p->data+2 << std::endl;
				}
			}
		}

		RakSleep(0);
	}

	rakPeer->Shutdown(100,0);
}

void run( int argc, char * argv[] ){
	if ( argc == 1 ){
		NetworkSystem::create("networkconfig.xml");
	} else {
		NetworkSystem::create(argv[1]);
	}

	if ( NetworkSystem::ready() ){
		if ( NetworkSystem::getNodeType() == NetworkSystem::Client ){
			//connect
			NetworkSystem::getRakPeerInterface()->Connect("127.0.0.1", "5000", 0, 0);
		}
		if ( NetworkSystem::getNodeType() == NetworkSystem::Server ){
			//make this node the owner -> generate a unique id
			loby.create();
			RPC3_REGISTER_FUNCTION(NetworkSystem::getRPC3(), &list);
		}
	} else {
		std::cerr << "Failed to start: check errors above" << std::endl;
	}

	go();
}


/*int main( int argc, char * argv[] ){
	if ( argc == 1 ){
		NetworkSystem::create("networkconfig.xml");
	} else {
		NetworkSystem::create(argv[1]);
	}
}*/
