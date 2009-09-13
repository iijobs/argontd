#ifndef _INSTANCING_H_H
#define _INSTANCING_H_H

#include <Ogre.h>
using namespace Ogre;

#include <vector>
using std::vector;

#include <string>
using std::string;

class Positioner {
	
public:
	
};

class Instancing
{
public:

	static const size_t MAXOBJECTSPERBATCH = 80;

	enum CurrentGeomOpt{
		INSTANCE_OPT,		//using instanced (fast but perhaps not suported)
		ENTITY_OPT,			//normal geometry (if instanced does not work)
		STATIC_OPT			//static geometry (cannot move)
	};

private:

	size_t numRender;

protected:

	/**
	 *	Scenemanager
	 */
	SceneManager * sceneMgr;

	/**
	 *	The name of the mesh
	 */
	string mesh;

	/**
	 *	Name of the instances
	 */
	string name;

	/**
	 *	ammount of objects
	 */
	size_t objectCount;

	/**
	 * The type of rendering system
	 */
	CurrentGeomOpt currentGeomOpt;

	/**
	 * List with all instances
	 */

	//Filled when instancing is used
	vector <InstancedGeometry *> renderInstance;

	//Filled when static geometry is used
	vector <StaticGeometry *> renderStatic;

	//Filled when non entity geometry is used
	vector <Entity *> renderEntity;
	vector <SceneNode *> nodes; 

	/**
	 * List with position matrices range (0 - objectCount-1)
	 */
	vector <Vector3> posMatrices;

private:

	//create/destroy instanced geometry
	void createInstanceGeom();
	void destroyInstanceGeom();

	//helper functions for instanced geometry
	void setupInstancedMaterialToEntity(Entity*);
	String buildInstancedMaterial(const String &);

	//create/destroy static geometry
	void createStaticGeom();
	void destroyStaticGeom();

	//create/destroy entity geometry
	void createEntityGeom();
	void destroyEntityGeom();

public:

	//-----------------------------------------------------------------------
	Instancing( CurrentGeomOpt instancingType, size_t objectCount, const string& mesh, const string& name, const vector <Vector3>& posMatrices, SceneManager * sceneMgr );

	//-----------------------------------------------------------------------
	~Instancing();

	//-----------------------------------------------------------------------
	void createCurrentGeomOpt();

	//-----------------------------------------------------------------------
	void destroyCurrentGeomOpt();

	//-----------------------------------------------------------------------
	void setCurrentGeometryOpt(CurrentGeomOpt opt);
};

#endif