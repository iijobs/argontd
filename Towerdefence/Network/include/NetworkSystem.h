#pragma once

#include <string>
using std::string;

#include <raknet/RakPeerInterface.h>
#include <RPC3.h>

class NetworkSystem
{
public:

	/**
	 * Create a network system from given config, if success will return true
	 * @param config
	 * @return success
	 */
	static bool create( const string& config );

	/**
	 * Check if network system is ready
	 */
	static bool ready();

	/**
	 * Destroy
	 */
	static void destroy();

	/**
	 * Get RakPeerInterface
	 */
	static RakPeerInterface * getRakPeerInterface(){
		return mPeer;
	}

	/**
	 * Get RPC3
	 */
	static RakNet::RPC3 * getRPC3(){
		return mRPC3;
	}

	/**
	 * Get NetworkIDManager
	 */
	static NetworkIDManager * getNetworkIdManager(){
		return mNetworkIDManager;
	}

private:

	/**
	 * RPC instance
	 */
	static RakNet::RPC3 * mRPC3;

	/**
	 * NetworkIDManager
	 */
	static NetworkIDManager * mNetworkIDManager;

	/**
	 * Raknet peer
	 */
	static RakPeerInterface * mPeer;

	NetworkSystem(void);

	~NetworkSystem(void);
};
