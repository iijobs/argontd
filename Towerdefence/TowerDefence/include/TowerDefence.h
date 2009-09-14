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

	void createIntroGUI() {
		QuickGUI::Root::getSingleton().setDefaultFontName("micross.20");

		// Create Sheet
		QuickGUI::SheetDesc* sd = QuickGUI::DescManager::getSingleton().getDefaultSheetDesc();
		sd->widget_dimensions.size = QuickGUI::Size(mRenderWindow->getWidth(),mRenderWindow->getHeight());
		mSheetFromFile = QuickGUI::SheetManager::getSingleton().createSheet(sd);
		mGUIManager->setActiveSheet(mSheetFromFile);

		//ofset top
		int height = (sd->widget_dimensions.size.height/2) - (400/2);	//window vert size/2 - total vert menu size /2
		int topleft_x = (sd->widget_dimensions.size.width/2) - (384/2);	//window hor size/2 - total hor menu size /2

		// create Main menu

		//common stuff
		QuickGUI::ButtonDesc* bd = QuickGUI::DescManager::getSingleton().getDefaultButtonDesc();
		bd->widget_dimensions.size = QuickGUI::Size(384,64);
		bd->widget_dragable = false;

		QuickGUI::ImageDesc * interbtn = QuickGUI::DescManager::getSingleton().getDefaultImageDesc();
		interbtn->widget_dimensions.size = QuickGUI::Size(384,16);
		interbtn->widget_dragable = false;

		//SP		
		bd->widget_skinTypeName = "singleplayer";
		bd->widget_name = "SinglePlayer";
		bd->widget_dimensions.position = QuickGUI::Point(topleft_x,height);		
		QuickGUI::Button * singleplayerbtn = mGUIManager->getActiveSheet()->createButton(bd);
		singleplayerbtn->addWidgetEventHandler(QuickGUI::WIDGET_EVENT_MOUSE_CLICK, &TowerDefence::onSinglePlayerClicked, this);
		height += 64;

		//create image between menu 1 2		
		interbtn->image_imageName = "menu12.png";		
		interbtn->widget_dimensions.position = QuickGUI::Point(topleft_x,height);		
		mGUIManager->getActiveSheet()->createImage(interbtn);
		height += 16;	

		//Internet
		bd->widget_skinTypeName = "internet";
		bd->widget_name = "Internet";
		bd->widget_dimensions.position = QuickGUI::Point(topleft_x,height);
		QuickGUI::Button * internetbtn = mGUIManager->getActiveSheet()->createButton(bd);
		internetbtn->addWidgetEventHandler(QuickGUI::WIDGET_EVENT_MOUSE_CLICK, &TowerDefence::onInternetClicked, this);
		height += 64;

		//create image between menu 2 3
		interbtn->image_imageName = "menu23.png";
		interbtn->widget_dimensions.position = QuickGUI::Point(topleft_x,height);
		mGUIManager->getActiveSheet()->createImage(interbtn);
		height += 16;	

		//Lan
		bd->widget_skinTypeName = "lan";
		bd->widget_name = "Lan";
		bd->widget_dimensions.position = QuickGUI::Point(topleft_x,height);
		QuickGUI::Button * lanbtn = mGUIManager->getActiveSheet()->createButton(bd);
		lanbtn->addWidgetEventHandler(QuickGUI::WIDGET_EVENT_MOUSE_CLICK, &TowerDefence::onLanClicked, this);
		height += 64;

		//create image between menu 3 4
		interbtn->image_imageName = "menu34.png";
		interbtn->widget_dimensions.position = QuickGUI::Point(topleft_x,height);
		mGUIManager->getActiveSheet()->createImage(interbtn);
		height += 16;

		//Options
		bd->widget_skinTypeName = "options";
		bd->widget_name = "Options";
		bd->widget_dimensions.position = QuickGUI::Point(topleft_x,height);		
		QuickGUI::Button * optionsbtn = mGUIManager->getActiveSheet()->createButton(bd);
		optionsbtn->addWidgetEventHandler(QuickGUI::WIDGET_EVENT_MOUSE_CLICK, &TowerDefence::onOptionsClicked, this);
		height += 64;

		//create image between menu 4 5
		interbtn->image_imageName = "menu45.png";
		interbtn->widget_dimensions.position = QuickGUI::Point(topleft_x,height);
		mGUIManager->getActiveSheet()->createImage(interbtn);
		height += 16;

		//EXIT
		bd->widget_skinTypeName = "exit";
		bd->widget_name = "Exit";
		bd->widget_dimensions.position = QuickGUI::Point(topleft_x,height);
		QuickGUI::Button * exitbtn = mGUIManager->getActiveSheet()->createButton(bd);
		exitbtn->addWidgetEventHandler(QuickGUI::WIDGET_EVENT_MOUSE_CLICK, &TowerDefence::onExitClicked, this);
		height += 64;

		//reset to default
		bd->resetToDefault();
		interbtn->resetToDefault();
	}

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
