/*
 * Room.h
 *
 *  Created on: Sep 27, 2009
 *      Author: arutha
 */

#ifndef ROOM_H_
#define ROOM_H_

#include "raknet/BitStream.h"

class Room {
private:

	friend RakNet::BitStream& operator<<(RakNet::BitStream&, Room&);

	friend RakNet::BitStream& operator>>(RakNet::BitStream&, Room&);

	int players;

	int maxplayers;

public:
	Room();

	Room( int maxplayers ):
		maxplayers(maxplayers){
	}

	virtual ~Room();

	void join(){
		players++;
	}

	void leave(){
		players--;
	}
};

RakNet::BitStream& operator<<(RakNet::BitStream& out, Room& in)
{
	in.players;
	return out;
}

RakNet::BitStream& operator>>(RakNet::BitStream& in, Room& out)
{
	//bool success = in.ReadNormVector(out.x,out.y,out.z);
	//assert(success);
	return in;
}

#endif /* ROOM_H_ */
