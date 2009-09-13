#include "Foliage.h"

#include "Random.h"

#include "TowerDefence.h"

#include <math.h>
#include <fstream>
using std::fstream;

using std::pair;

bool FoliageConfig::load( string filename ){
	char buffer [1024];
	string configfile = "config.foliage";
	fstream config(configfile.c_str());

	if ( config.is_open()) {
		FoliageConfig foliageConfig;
		
		while ( !config.eof() ){
			config.getline(buffer,1024);
			int read = config.gcount();
			//TODO do actual config file
		}
	}
	else {
		//return false;
	}

	//this should come from config
	image = "foliage.png";
	groupname = "General";

	meshes.insert(pair<int,string>(0,"robot.mesh") );
	meshes.insert(pair<int,string>(1,"razor.mesh") );
	meshes.insert(pair<int,string>(2,"knot.mesh") );

	colormap.insert(pair<int,ColourValue>(0, ColourValue(1.0,0.0,0.0,0.0)) );	// red is first type
	colormap.insert(pair<int,ColourValue>(1, ColourValue(0.0,1.0,0.0,0.0)) );	// blue is second type
	colormap.insert(pair<int,ColourValue>(2, ColourValue(0.0,0.0,1.0,0.0)) );	// green is third type

	density.insert(pair<int,float>(0,0.6f) );
	density.insert(pair<int,float>(1,0.6f) );
	density.insert(pair<int,float>(2,0.6f) );

	size = 1500;

	draw_radius = 100;

	return true;
}

FoliageFrameListener::FoliageFrameListener( TowerDefence * main, const string& config ):
	mMain(main), mInstances(0), mPrevPosition(0,0,0)
{
	Ogre::Root::getSingleton().addFrameListener(this);
	setup(config);
}

FoliageFrameListener::~FoliageFrameListener(void)
{
	delete mInstances;
}

bool FoliageFrameListener::updateGeom(){
	Random randomGen;

		//check if not to high/low -> draw nothing if so
		//if ( abs(pos.y) < draw_radius ){
		//}

		//delete mInstances;

		//convert position to pixel coordinates 
		//

		
		/*for( size_t i = 0; i < mFoliageConfig.draw_radius; i++ ){
			for ( size_t j = 0; j < mFoliageConfig.draw_radius; j++ ){
				int px = (i - mFoliageConfig.draw_radius + pos.x) * mPixelRatio;
				int py = (i - mFoliageConfig.draw_radius + pos.y) * mPixelRatio;
				if ( (px >= 0) && (px <= mFoliageMap.getWidth()) && (py >= 0) && (py <= mFoliageMap.getHeight()) ){
					ColourValue c = mFoliageMap.getColourAt(px,py,0);
					for ( int k = 0; k < mFoliageConfig.colormap.size(); k++){				
						float distance = sqrtf( pow(c.r - mFoliageConfig.colormap[k].r,2) + pow(c.b - mFoliageConfig.colormap[k].b,2) + pow(c.g - mFoliageConfig.colormap[k].g,2) + pow(c.a - mFoliageConfig.colormap[k].a,2) );
						float random = randomGen.next(0, 2 );
						if ( random > distance ){
							
						}
					}
				}
			}
		}*/	

		/*vector<Vector3> posMatrices;
		posMatrices.push_back(pos + Vector3(50,-100,50));
		posMatrices.push_back(pos + Vector3(-50,-100,50));
		posMatrices.push_back(pos + Vector3(-50,-100,-50));
		posMatrices.push_back(pos + Vector3(50,-100,-50));*/

		//mInstances = new Instancing( Instancing::STATIC_OPT, 4, mFoliageConfig.meshes[0], mFoliageConfig.meshes[0], posMatrices, mMain->getSceneManager() );

/*
		

		vector<int> times;
		times.reserve(folconfig.colormap.size());
		times.resize(folconfig.colormap.size());
		for ( size_t i = 0; i < times.size(); i++ ){
			times[i] = 0;
		}

		instances.reserve(folconfig.colormap.size());
		instances.resize(folconfig.colormap.size());

		vector < vector<Vector3> > posMatrices;
		posMatrices.reserve(folconfig.colormap.size());
		posMatrices.resize(folconfig.colormap.size());

		//RaySceneQuery * raySceneQuery = new DefaultRaySceneQuery(sceneMgr);

		for( size_t i = 0; i < foliageMap.getWidth(); i++ ){
			for ( size_t j = 0; j < foliageMap.getHeight(); j++ ){
				//get the pixel color
				ColourValue c = foliageMap.getColourAt(i,j,0);
				
				for ( int k = 0; k < folconfig.colormap.size(); k++){
					//calculate the distance between the colors
					float distance = sqrtf( pow(c.r - folconfig.colormap[k].r,2) + pow(c.b - folconfig.colormap[k].b,2) + pow(c.g - folconfig.colormap[k].g,2) + pow(c.a - folconfig.colormap[k].a,2) );

					//max dist ( (1-0)^2 + (1-0)^2 + (1-0)^2 + (1-0)^2 )^1/2 = 2					
					//draw random nr between 0 - max dist between points (=2)
					float random = randomGen.next(0, 2 );
					//if distance is small the probability should be big => ">" operation
					if ( random > distance ){						
						random = randomGen.next(0,1);
						if ( random < folconfig.density[k] ){
							times[k]++;
							posMatrices[k].push_back(Vector3 (i , 50, j));
						}
						Ray updateRay(pos,Vector3::NEGATIVE_UNIT_Y);
						raySceneQuery->setRay(updateRay);
						RaySceneQueryResult& qryResult = raySceneQuery->execute();
						RaySceneQueryResult::iterator i = qryResult.begin();
						if (i != qryResult.end() && i->worldFragment)
						{
							pos.y = i->worldFragment->singleIntersection.y -5;
						}				
					}
				}				
			}
		}

		//delete raySceneQuery;  


		for ( int k = 0; k < folconfig.colormap.size(); k++){
			instances[k] = new Instancing( Instancing::STATIC_OPT, times[k], folconfig.meshes[k], folconfig.meshes[k], posMatrices[k], sceneMgr );
		}*/




	return true;
}

bool FoliageFrameListener::frameRenderingQueued(const Ogre::FrameEvent& evt){
	/*Camera * cam = mMain->getCamera();
	const Vector3& pos = cam->getPosition();

	//update geom when big move occurs
	if ( pos.squaredDistance(mPrevPosition) > mFoliageConfig.draw_radius * mFoliageConfig.draw_radius ){
		//update GEOM
		mPrevPosition = pos;
		updateGeom();		
	}	*/
	return true;
}

bool FoliageFrameListener::setup( const String& config ){
	if ( mFoliageConfig.load(config) ){
		mFoliageMap.load(mFoliageConfig.image, mFoliageConfig.groupname );
		mPixelRatio = (float) mFoliageMap.getWidth() / mFoliageConfig.size;
		mPixelSize = mPixelRatio * mFoliageConfig.size;

		//do initial drawing here
	//	mPrevPosition = mMain->getCamera()->getPosition();
		updateGeom();		
		return true;
	} else {
		LogManager::getSingleton().logMessage("Failed to load foliage config");
		return false;
	}
}