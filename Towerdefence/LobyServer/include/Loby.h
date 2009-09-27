/*
 * Loby.h
 *
 *  Created on: Sep 27, 2009
 *      Author: arutha
 */

#ifndef LOBY_H_
#define LOBY_H_

#include <list>
#include <raknet/BitStream.h>

#include "Room.h"

class Loby {

private:

	std::list<Room> rooms;

public:
	Loby();

	virtual ~Loby();


};

RakNet::BitStream& operator<<(RakNet::BitStream& out, Loby& in)
{
	//out.WriteNormVector(in.x,in.y,in.z);
	return out;
}
RakNet::BitStream& operator>>(RakNet::BitStream& in, Loby& out)
{
	//bool success = in.ReadNormVector(out.x,out.y,out.z);
	//assert(success);
	return in;
}

#endif /* LOBY_H_ */
