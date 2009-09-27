#ifndef LOBY_H_
#define LOBY_H_

#include <iostream>
#include <list>

#include "NetworkObject.h"
#include "RPC3.h"
#include <raknet/BitStream.h>
#include <raknet/NetworkIDObject.h>

#include "Room.h"
#include "Client.h"

class Loby : public NetworkObject {

private:

	friend RakNet::BitStream& operator<<(RakNet::BitStream&, Loby&);

	friend RakNet::BitStream& operator>>(RakNet::BitStream&, Loby&);

	std::list<Room> rooms;

	std::list<Client> clients;

private:

	void update(){
		for ( std::list<Client>::iterator i = clients.begin(); i != clients.end(); i++  ){
			//i->onLobyUpdate();
		}
	}

public:

	Loby(){
	}

	virtual ~Loby();

	virtual void registerInterface(){
		RPC3_REGISTER_FUNCTION(NetworkSystem::getRPC3(), &Loby::create);
		RPC3_REGISTER_FUNCTION(NetworkSystem::getRPC3(), &Loby::destroy);
	}

	/**
	 * Create a room
	 * @param room
	 */
	void create ( Room& room, RakNet::RPC3 * rpc3 ){
		std::cout << "Room created by " << room.getHost().getName() << std::endl;
		rooms.push_back(room);
	}

	/**
	 * Destroy a room
	 * @param room
	 */
	void destroy ( Room& room, RakNet::RPC3 * rpc3 ){
		std::cout << "Room destroyed" << std::endl;
		rooms.remove(room);
	}
};

//operator<< , operator>>

RakNet::BitStream& operator<<(RakNet::BitStream& out, Loby& in)
{
	out.Write((int)in.rooms.size());
	for ( std::list<Room>::iterator i = in.rooms.begin(); i != in.rooms.end(); i++ ){
		out << *i;
	}
	return out;
}

RakNet::BitStream& operator>>(RakNet::BitStream& in, Loby& out)
{
	int rooms = 0;
	assert(in.Read(rooms));
	out.rooms.resize(rooms);
	for ( std::list<Room>::iterator i = out.rooms.begin(); i != out.rooms.end(); i++ ){
		in >> *i;
	}
	return in;
}

#endif /* LOBY_H_ */
