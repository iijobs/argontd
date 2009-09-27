#ifndef CLIENT_H_
#define CLIENT_H_

#include "NetworkObject.h"
#include "RPC3.h"
#include "raknet/BitStream.h"
#include "raknet/NetworkIDObject.h"
#include "raknet/StringCompressor.h"
#include <string>

class Client : public NetworkObject {

private:

	friend RakNet::BitStream& operator<<(RakNet::BitStream&, Client&);

	friend RakNet::BitStream& operator>>(RakNet::BitStream&, Client&);

	std::string name;

public:
	Client():
		name(""){
	}

	Client( const std::string& name ):
		name(name){
	}

	virtual ~Client();

	virtual void registerInterface(){
		RPC3_REGISTER_FUNCTION(NetworkSystem::getRPC3(), &Client::onLobyUpdate);
	}

	std::string& getName(){
		return name;
	}

	void onLobyUpdate( RakNet::RPC3 * rpc3 ){

	}
};

//operator<< , operator>>

RakNet::BitStream& operator<<(RakNet::BitStream& out, Client& in)
{
	stringCompressor->EncodeString(in.name.c_str(),256,&out);
	return out;
}

RakNet::BitStream& operator>>(RakNet::BitStream& in, Client& out)
{
	char name [256];
	assert(stringCompressor->DecodeString(name,256,&in));
	out.name = std::string(name);
	return in;
}

#endif /* CLIENT_H_ */
