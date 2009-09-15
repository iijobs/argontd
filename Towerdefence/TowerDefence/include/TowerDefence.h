#ifndef _TERRAINAPPLICATION_H_
#define _TERRAINAPPLICATION_H_

#include <OgreConfigFile.h>
#include <OgreStringConverter.h>
#include <OgreException.h>
#include <OgreString.h>
#include <string>
using std::string;
#include "Window.h"

#include "QuickGUI.h"


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

	/**
	 * Called after creation of scene, can be used to create GUI, attach frame/key/mouse listeners etc
	 */
	virtual void final();

	//			GUI			//

	void createIntroGUI();

	void createOptionsGUI();

	/**
	 * Callback when main clicked
	 * @param event
	 */
	void onOkClicked(const QuickGUI::EventArgs& event){
		this->createIntroGUI();
	};	

	/**
	 * Callback when main clicked
	 * @param event
	 */
	void onBackClicked(const QuickGUI::EventArgs& event){
		this->createIntroGUI();
	};	

	/**
	 * Callback when exit clicked
	 * @param event
	 */
	void onExitClicked(const QuickGUI::EventArgs& event){
		this->close();
	};

	/**
	 * Callback when options clicked
	 * @param event
	 */
	void onOptionsClicked(const QuickGUI::EventArgs& event){
		this->createOptionsGUI();
	};

	/**
	 * Callback when SinglePlayer clicked
	 * @param event
	 */
	void onSinglePlayerClicked(const QuickGUI::EventArgs& event){
	
	};

	/**
	 * Callback when Lan clicked
	 * @param event
	 */
	void onLanClicked(const QuickGUI::EventArgs& event){
	
	};


	/**
	 * Callback when Internet clicked
	 * @param event
	 */
	void onInternetClicked(const QuickGUI::EventArgs& event){
	
	};
};

#endif
