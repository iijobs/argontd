#ifndef _TERRAINAPPLICATION_H_
#define _TERRAINAPPLICATION_H_

#include <OgreConfigFile.h>
#include <OgreStringConverter.h>
#include <OgreException.h>
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

		//SP
		QuickGUI::ButtonDesc* singlePlayerBD = QuickGUI::DescManager::getSingleton().getDefaultButtonDesc();
		singlePlayerBD->button_imageName = "singleplayer.png";
		singlePlayerBD->widget_name = "SinglePlayer";
		singlePlayerBD->widget_dimensions.size = QuickGUI::Size(384,64);
		singlePlayerBD->widget_dimensions.position = QuickGUI::Point(topleft_x,height);
		singlePlayerBD->widget_dragable = false;
		QuickGUI::Button * singleplayerbtn = mGUIManager->getActiveSheet()->createButton(singlePlayerBD);
		singleplayerbtn->addWidgetEventHandler(QuickGUI::WIDGET_EVENT_MOUSE_CLICK, &TowerDefence::onSinglePlayerClicked, this);
		height += 64;

		//create image between menu 1 2
		QuickGUI::ImageDesc * menu12 = QuickGUI::DescManager::getSingleton().getDefaultImageDesc();
		menu12->image_imageName = "menu12.png";
		menu12->widget_dimensions.size = QuickGUI::Size(384,16);
		menu12->widget_dimensions.position = QuickGUI::Point(topleft_x,height);
		menu12->widget_dragable = false;
		mGUIManager->getActiveSheet()->createImage(menu12);
		height += 16;	

		//Internet
		QuickGUI::ButtonDesc* internetBD = QuickGUI::DescManager::getSingleton().getDefaultButtonDesc();
		internetBD->button_imageName = "internet.png";
		internetBD->widget_name = "Internet";
		internetBD->widget_dimensions.size = QuickGUI::Size(384,64);
		internetBD->widget_dimensions.position = QuickGUI::Point(topleft_x,height);
		internetBD->widget_transparencyPicking = true;
		internetBD->widget_dragable = false;
		QuickGUI::Button * internetbtn = mGUIManager->getActiveSheet()->createButton(internetBD);
		internetbtn->addWidgetEventHandler(QuickGUI::WIDGET_EVENT_MOUSE_CLICK, &TowerDefence::onInternetClicked, this);
		height += 64;

		//create image between menu 2 3
		QuickGUI::ImageDesc * menu23 = QuickGUI::DescManager::getSingleton().getDefaultImageDesc();
		menu23->image_imageName = "menu23.png";
		menu23->widget_dimensions.size = QuickGUI::Size(384,16);
		menu23->widget_dimensions.position = QuickGUI::Point(topleft_x,height);
		menu23->widget_dragable = false;
		mGUIManager->getActiveSheet()->createImage(menu23);
		height += 16;	

		//Lan
		QuickGUI::ButtonDesc* lanDB = QuickGUI::DescManager::getSingleton().getDefaultButtonDesc();
		lanDB->button_imageName = "lan.png";
		lanDB->widget_name = "Lan";
		lanDB->widget_dimensions.size = QuickGUI::Size(384,64);
		lanDB->widget_dimensions.position = QuickGUI::Point(topleft_x,height);
		lanDB->widget_transparencyPicking = true;
		lanDB->widget_dragable = false;
		QuickGUI::Button * lanbtn = mGUIManager->getActiveSheet()->createButton(lanDB);
		lanbtn->addWidgetEventHandler(QuickGUI::WIDGET_EVENT_MOUSE_CLICK, &TowerDefence::onLanClicked, this);
		height += 64;

		//create image between menu 3 4
		QuickGUI::ImageDesc * menu34 = QuickGUI::DescManager::getSingleton().getDefaultImageDesc();
		menu34->image_imageName = "menu34.png";
		menu34->widget_dimensions.size = QuickGUI::Size(384,16);
		menu34->widget_dimensions.position = QuickGUI::Point(topleft_x,height);
		menu34->widget_dragable = false;
		mGUIManager->getActiveSheet()->createImage(menu34);
		height += 16;

		//Options
		QuickGUI::ButtonDesc* optionsDB = QuickGUI::DescManager::getSingleton().getDefaultButtonDesc();
		optionsDB->button_imageName = "options.png";
		optionsDB->widget_name = "Options";
		optionsDB->widget_dimensions.size = QuickGUI::Size(384,64);
		optionsDB->widget_dimensions.position = QuickGUI::Point(topleft_x,height);
		optionsDB->widget_transparencyPicking = true;
		optionsDB->widget_dragable = false;
		QuickGUI::Button * optionsbtn = mGUIManager->getActiveSheet()->createButton(optionsDB);
		optionsbtn->addWidgetEventHandler(QuickGUI::WIDGET_EVENT_MOUSE_CLICK, &TowerDefence::onOptionsClicked, this);
		height += 64;

		//create image between menu 4 5
		QuickGUI::ImageDesc * menu45 = QuickGUI::DescManager::getSingleton().getDefaultImageDesc();
		menu45->image_imageName = "menu45.png";
		menu45->widget_dimensions.size = QuickGUI::Size(384,16);
		menu45->widget_dimensions.position = QuickGUI::Point(topleft_x,height);
		menu45->widget_dragable = false;
		mGUIManager->getActiveSheet()->createImage(menu45);
		height += 16;

		//EXIT
		QuickGUI::ButtonDesc* exitBD = QuickGUI::DescManager::getSingleton().getDefaultButtonDesc();
		exitBD->button_imageName = "exit.png";
		exitBD->widget_name = "Exit";
		exitBD->widget_dimensions.size = QuickGUI::Size(384,64);
		exitBD->widget_dimensions.position = QuickGUI::Point(topleft_x,height);
		exitBD->widget_transparencyPicking = true;
		exitBD->widget_dragable = false;
		QuickGUI::Button * exitbtn = mGUIManager->getActiveSheet()->createButton(exitBD);
		exitbtn->addWidgetEventHandler(QuickGUI::WIDGET_EVENT_MOUSE_CLICK, &TowerDefence::onExitClicked, this);
		height += 64;
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
