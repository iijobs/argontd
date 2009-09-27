/*
 * NetworkObject.h
 *
 *  Created on: Sep 27, 2009
 *      Author: arutha
 */

#ifndef NETWORKOBJECT_H_
#define NETWORKOBJECT_H_

#include "raknet/NetworkIDObject.h"
#include "NetworkSystem.h"

class NetworkObject : public NetworkIDObject {
public:
	NetworkObject(){
	}

	virtual ~NetworkObject(){
	}

	void create(){
		SetNetworkIDManager(NetworkSystem::getNetworkIdManager());
		registerInterface();
	}

	/**
	 * Register all functions that can be called remotely
	 */
	virtual void registerInterface() = 0;
};

#endif /* NETWORKOBJECT_H_ */
