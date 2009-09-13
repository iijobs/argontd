#include "Instancing.h"


Instancing::Instancing( CurrentGeomOpt instancingType, size_t objectCount, const string& mesh, const string& name, const vector <Vector3>& posMatrices, SceneManager * sceneMgr ):
	sceneMgr(sceneMgr),
	mesh(mesh),
	name(name),
	objectCount(objectCount),
	currentGeomOpt(instancingType),
	posMatrices(posMatrices)
{ 
	createCurrentGeomOpt();
}

//-----------------------------------------------------------------------
Instancing::~Instancing()
{
	destroyCurrentGeomOpt();
}

//-----------------------------------------------------------------------
void Instancing::createCurrentGeomOpt()
{
	//calculate the amount of renders
	numRender = objectCount / MAXOBJECTSPERBATCH;
	if ( objectCount % MAXOBJECTSPERBATCH > 0 )	//add one if some rest exists
		numRender++;

	//load mesh in memory
	MeshPtr m = MeshManager::getSingleton().getByName(name);
	if (m.isNull ()){
		m = MeshManager::getSingleton ().load (mesh, ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME);
	}
	
	/*//set up position matrices for each instace
	posMatrices.resize (objectCount);
	posMatrices.reserve (objectCount);

	//TODO some way so that an algoritm can be pluged in
	//set position matrices
	for (size_t i = 0; i < objectCount; i++)
	{
		posMatrices[i] = Vector3::ZERO;
	}*/
	
	//do creation depending on the style
	switch(currentGeomOpt)
	{
		case INSTANCE_OPT:createInstanceGeom();break;
		case STATIC_OPT:createStaticGeom ();break;
		case ENTITY_OPT: createEntityGeom ();break;
	}
}

//-----------------------------------------------------------------------
void Instancing::destroyCurrentGeomOpt()
{
	switch(currentGeomOpt)
	{
		case INSTANCE_OPT:destroyInstanceGeom();break;
		case STATIC_OPT:destroyStaticGeom ();break;
		case ENTITY_OPT: destroyEntityGeom ();break;
	}

	posMatrices.clear();
}

//-----------------------------------------------------------------------
void Instancing::createInstanceGeom()
{
	if (Root::getSingleton ().getRenderSystem ()->getCapabilities ()->hasCapability (RSC_VERTEX_PROGRAM) == false)
	{
		//OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "Your video card doesn't support batching", "Demo_Instance::createScene");
		//if not posible change to static		
		currentGeomOpt = STATIC_OPT;
		createStaticGeom();
	}

	//create a instance of the mesg that will be copied
	Entity *ent = sceneMgr->createEntity(name, mesh);	

	//set size of references to the batches.
	renderInstance.reserve(numRender);
	renderInstance.resize(numRender);

	//load a mesh to read data from.	
	InstancedGeometry* batch = new InstancedGeometry(sceneMgr, name + "s" );
	
	//set some properties
	batch->setCastShadows(true);
	batch->setBatchInstanceDimensions (Vector3(1000000, 1000000, 1000000));
	const size_t batchSize = (objectCount > MAXOBJECTSPERBATCH) ? MAXOBJECTSPERBATCH : objectCount;
	
	//setupInstancedMaterialToEntity(ent);	
	
	for(size_t i = 0; i < batchSize ; i++)
	{
		batch->addEntity(ent, Vector3::ZERO);
	}
	batch->setOrigin(Vector3::ZERO);

	batch->build();


	for (size_t k = 0; k < numRender-1; k++)
	{
		batch->addBatchInstance();
	}
	size_t i = 0;
	InstancedGeometry::BatchInstanceIterator regIt = batch->getBatchInstanceIterator();
	size_t baseIndexForBatch = 0;
	size_t k = 0;
	while (regIt.hasMoreElements ())
	{

		InstancedGeometry::BatchInstance *r = regIt.getNext();

		InstancedGeometry::BatchInstance::InstancedObjectIterator bit = r->getObjectIterator();
		int j = 0;
		while(bit.hasMoreElements())
		{
			InstancedGeometry::InstancedObject* obj = bit.getNext();

			const Vector3 position (posMatrices[k][j]);								
			obj->setPosition(position);
			++j;

		}
		k++;
		
	}
	batch->setVisible(true);
	renderInstance[0] = batch;

	sceneMgr->destroyEntity (ent);
}
void Instancing::setupInstancedMaterialToEntity(Entity*ent)
{
	for (Ogre::uint i = 0; i < ent->getNumSubEntities(); ++i)
	{
		SubEntity* se = ent->getSubEntity(i);
		String materialName= se->getMaterialName();
		se->setMaterialName(buildInstancedMaterial(materialName));
	}
}
String Instancing::buildInstancedMaterial(const String &originalMaterialName)
{

	// already instanced ?
	if (StringUtil::endsWith (originalMaterialName, "/instanced"))
		return originalMaterialName;

	MaterialPtr originalMaterial = MaterialManager::getSingleton ().getByName (originalMaterialName);

	// if originalMat doesn't exists use "Instancing" material name
	const String instancedMaterialName (originalMaterial.isNull() ? "Instancing" : originalMaterialName + "/Instanced");
	MaterialPtr  instancedMaterial = MaterialManager::getSingleton ().getByName (instancedMaterialName);

	// already exists ?
	if (instancedMaterial.isNull())
	{
		instancedMaterial = originalMaterial->clone(instancedMaterialName);
		instancedMaterial->load();
		Technique::PassIterator pIt = instancedMaterial->getBestTechnique ()->getPassIterator();
		while (pIt.hasMoreElements())
		{

			Pass * const p = pIt.getNext();
			p->setVertexProgram("Instancing", false);
			p->setShadowCasterVertexProgram("InstancingShadowCaster");


		}
	}
	instancedMaterial->load();
	return instancedMaterialName;
}
//-----------------------------------------------------------------------
void Instancing::destroyInstanceGeom()
{
	delete renderInstance[0];
	renderInstance.clear();
}

/**
 *	StaticGeom
 */

//-----------------------------------------------------------------------
void Instancing::createStaticGeom()
{
	//create a instance of the mesg that will be copied
	Entity *ent = sceneMgr->createEntity(name, mesh);	

	//set size of references to the batches.
	renderStatic.reserve (numRender);
	renderStatic.resize (numRender);

	StaticGeometry * geom = new StaticGeometry (sceneMgr, name + "s");

	geom->setRegionDimensions (Vector3(1000000, 1000000, 1000000));
	for (size_t i = 0; i < objectCount; i++)
	{
		geom->addEntity (ent, posMatrices[i]);
	}

	geom->setCastShadows(true);
	geom->build ();
	renderStatic[0] = geom;

	//remove instance that was used to copy
	sceneMgr->destroyEntity (ent);
}
//-----------------------------------------------------------------------
void Instancing::destroyStaticGeom()
{
	delete renderStatic[0];
	renderStatic.clear();
}

/**
 *	EntityGeom
 */

//-----------------------------------------------------------------------
void Instancing::createEntityGeom()
{
	//set size of references to the objectCount.
	renderEntity.reserve (objectCount);
	renderEntity.resize (objectCount);

	nodes.reserve (objectCount);
	nodes.resize (objectCount);

	for (size_t i = 0; i < objectCount; i++)
	{
		nodes[i]=sceneMgr->getRootSceneNode()->createChildSceneNode("node" + StringConverter::toString(i));
		renderEntity[i]=sceneMgr->createEntity(name + StringConverter::toString(i), mesh);	
		nodes[i]->attachObject(renderEntity[i]);
		nodes[i]->setPosition(posMatrices[i]);
	}
}
//-----------------------------------------------------------------------
void Instancing::destroyEntityGeom()
{
	for (size_t i = 0; i < objectCount; i++)
	{
		String name = nodes[i]->getName();
		sceneMgr->destroySceneNode(name);
		sceneMgr->destroyEntity(renderEntity[i]);
	}
}

