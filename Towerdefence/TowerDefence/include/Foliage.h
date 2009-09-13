#ifndef _FOLIAGE_H_
#define _FOLIAGE_H_

#include "Instancing.h"

#include <string>
#include <vector>
#include <map>
using std::map;
using std::string;
using std::vector;

#include <Ogre.h>
using namespace Ogre;

/**
 *	Foliage config should contain all info to set up a Foliage class
 */
class FoliageConfig {
public:

	/**
	 * radius arround camera that should have foliage in it
	 */
	float draw_radius;

	/**
	 * World size
	 */
	float size;

	/**
	 *	Image url that contains the mapping image
	 */
	string image;

	/**
	 *	Name of the resource group to search for the image
	 */
	string groupname;

	/**
	 *	List with meshes
	 */
	map<int,string> meshes;

	/**
	 *	Mapping from color to mesh ID
	 */
	map<int,ColourValue> colormap;

	/**
	 *	Density of the meshes per square meter, range 0 - ...
	 */
	map<int,float> density;

	/**
	 * Load foliage config
	 * @param filename
	 * @return true if success, false if failed
	 */
	bool load( string filename );
};

class TowerDefence;

/**
 *	Implementation of foliage
 */
class FoliageFrameListener : public Ogre::FrameListener {
private:

	Vector3 mPrevPosition;

	FoliageConfig mFoliageConfig;

	Image mFoliageMap;

	/**
	 * mPixelRatio * mFoliageConfig.size = mFoliageMap.getWidth()
	 */
	float mPixelRatio;

	/**
	 * mPixelSize = mPixelRatio *  mFoliageConfig.size 
	 */
	float mPixelSize;

	TowerDefence * mMain;

	Instancing * mInstances;

	bool setup( const String& config );

	bool updateGeom();

public:

	FoliageFrameListener( TowerDefence * main, const string& config );

	virtual ~FoliageFrameListener();

	/**
	 * @see FrameListener
	 */
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
};


#endif