#ifndef _TERRAINAPPLICATION_H_
#define _TERRAINAPPLICATION_H_

#include <OgreConfigFile.h>
#include <OgreStringConverter.h>
#include <OgreException.h>
#include "Window.h"


class Main {

public:

	Main();

	~Main();

	/**
	 * Set up link to resources
	 */
	bool setResources(void);

		/**
	 * Show configure screen
	 */
	bool setConfiguration(void);

	/**
	 * Init libs eg for networking/GUI etc
	 */
	bool setLibs();

	/**
	 * Create window/scene etc
	 */
	bool createWindow();

	/**
	 * Load extra startup scripts
	 */
	bool setStartupResources(void);

	/**
	 *	Start rendering
	 */
    void go(void);

protected:
	/**
	 *	Ogre fields
	 */
	Ogre::Root * mRoot;

	Ogre::RenderWindow * mRenderWindow;

	Window * mWindow;

	//RakPeerInterface * mPeer;

};

/**
 * The actual tower defence window
 */
class TowerDefence : public Window
{

protected:

	QuickGUI::Sheet* mSheetFromFile;

public:

	TowerDefence( Ogre::RenderWindow* w );

    virtual ~TowerDefence();

	/**
	 * Create a scenemanager
	 * @return Ogre::SceneManager *
	 */
	Ogre::SceneManager * createSceneManager();

	/**
	 * Create a camera
	 * @return Ogre::Camera *
	 */
	Ogre::Camera * createCamera();

	/**
	 * Create a viewport
	 * @return Ogre::Viewport *
	 */
	Ogre::Viewport * createViewport();

	/**
	 * Create initial scene
	 */
	void createScene();

	virtual void final();

};

#endif