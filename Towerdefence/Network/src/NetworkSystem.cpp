#include "NetworkSystem.h"

#include "tinyxml.h"

#include <vector>
using std::vector;

#include <iostream>
using std::cerr;
using std::endl;

#include <raknet/NetworkIDManager.h>
#include <raknet/RakNetworkFactory.h>
#include <raknet/MessageIdentifiers.h>

RakNet::RPC3 * NetworkSystem::mRPC3 = 0;
NetworkIDManager * NetworkSystem::mNetworkIDManager = 0;
RakPeerInterface * NetworkSystem::mPeer = 0;


bool NetworkSystem::ready(){
	return mPeer && mRPC3 && mNetworkIDManager;
}

bool NetworkSystem::create( const string& config ){

	TiXmlDocument doc( config.c_str() );
	if ( !doc.LoadFile() ){
		return false;
	}

	//create PEER
	mPeer = RakNetworkFactory::GetRakPeerInterface();

	//create RPC3
	mRPC3 = new RakNet::RPC3();

	//create Network ID manager
	mNetworkIDManager = new NetworkIDManager();

	TiXmlDocument * document = doc.GetDocument();
	TiXmlHandle docHandle ( document );

	//check if server
	TiXmlElement * server = docHandle.FirstChildElement("server").Element();
	if ( server ){
		mType = NetworkSystem::Server;

		int mMaxConnections;
		if ( !server->Attribute("connections",&mMaxConnections) ){
			cerr << "missing 'connections' attribute in 'server' tag" << endl;
			destroy();
			return false;
		}

		vector<SocketDescriptor> interfaces;
		//loop over interfaces
		for( TiXmlElement * child = docHandle.FirstChildElement("server").FirstChildElement("interface").Element(); child; child = child->NextSiblingElement("interface") )
		{
			if ( child ){
				TiXmlHandle ifacehandle ( child );
				TiXmlText * ip = ifacehandle.FirstChild("ip").FirstChild().Text();
				TiXmlText * port = ifacehandle.FirstChild("port").FirstChild().Text();
				if ( ip && port ){
					SocketDescriptor sd;
					memcpy(sd.hostAddress,ip->Value(), sizeof(char) * 32);
					sd.port = atoi(port->Value());
					interfaces.push_back(sd);
				}
			}
		}

		if ( interfaces.empty() ){
			cerr << "no 'interfaces' specified in 'server' tag" << endl;
			destroy();
			return false;
		}

		//copy
		SocketDescriptor * mSocketDescriptions = new SocketDescriptor[interfaces.size()];
		for ( unsigned int i = 0; i < interfaces.size(); i++ ){
			mSocketDescriptions[i] = interfaces[i];
		}

		mNetworkIDManager->SetIsNetworkIDAuthority(true);
		mRPC3->SetNetworkIDManager(mNetworkIDManager);

		//start server
		mPeer->Startup(mMaxConnections,30, mSocketDescriptions, interfaces.size());

		delete [] mSocketDescriptions;
	}
	else {
		//check for client tag (should be there)
		TiXmlElement * client = docHandle.FirstChildElement("client").Element();
		if ( client ){
			mType = NetworkSystem::Client;
			mRPC3->SetNetworkIDManager(mNetworkIDManager);
			//mPeer->Connect("",0,0,0);
		} else {
			cerr << "no 'server' or 'client' tag" << endl;
			destroy();
			return false;
		}
	}

	//attach RPC
	mPeer->AttachPlugin(mRPC3);

	return true;
}

void NetworkSystem::destroy(){
	if ( mPeer ){
		mPeer->DetachPlugin(mRPC3);
		RakNetworkFactory::DestroyRakPeerInterface(mPeer);
	}
	mPeer = 0;

	if ( mRPC3 )
		delete mRPC3;
	mRPC3 = 0;

	if ( mNetworkIDManager)
		delete mNetworkIDManager;
	mNetworkIDManager = 0;
}

NetworkSystem::NetworkSystem(void)
{
}

NetworkSystem::~NetworkSystem(void)
{
}
