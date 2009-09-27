/*
 * Room.h
 *
 *  Created on: Sep 27, 2009
 *      Author: arutha
 */

#ifndef ROOM_H_
#define ROOM_H_

#include "NetworkObject.h"
#include "RPC3.h"
#include "raknet/BitStream.h"
#include "raknet/NetworkIDObject.h"


#include "Client.h"

/**
 * A room is a container with players
 */
class Room : public NetworkObject {
private:

	friend RakNet::BitStream& operator<<(RakNet::BitStream&, Room&);

	friend RakNet::BitStream& operator>>(RakNet::BitStream&, Room&);

	int players;

	int maxplayers;

	Client host;

public:

	/**
	 * Room constructor
	 */
	Room():
		maxplayers(0),
		players(0)
	{}


	Room( int maxplayers ):
		maxplayers(maxplayers),
		players(0){
	}

	/**
	 * Destructor
	 */
	virtual ~Room();

	virtual void registerInterface(){
		RPC3_REGISTER_FUNCTION(NetworkSystem::getRPC3(), &Room::join);
		RPC3_REGISTER_FUNCTION(NetworkSystem::getRPC3(), &Room::leave);
	}

	/**
	 * Join a room
	 */
	void join( RakNet::RPC3 * rpc3 ){
		players++;
	}

	/**
	 * Leave a room
	 */
	void leave( RakNet::RPC3 * rpc3 ){
		players--;
	}

	Client& getHost(){
		return host;
	}

	/**
	 * Compare operation
	 * @param opp
	 * @return true if same, false if not
	 */
	bool operator==( Room& opp ) {
		return this->GetNetworkID() == opp.GetNetworkID();
	}
};

RakNet::BitStream& operator<<(RakNet::BitStream& out, Room& in)
{
	out.Write(in.players);
	out.Write(in.maxplayers);
	return out;
}

RakNet::BitStream& operator>>(RakNet::BitStream& in, Room& out)
{
	assert(in.Read(out.players));
	assert(in.Read(out.maxplayers));
	return in;
}

#endif /* ROOM_H_ */
