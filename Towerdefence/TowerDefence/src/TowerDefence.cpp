
#include "TowerDefence.h"

#include "DefaultFrameListener.h"

#include "NetworkSystem.h"




/**********************************************************************
OS X Specific Resource Location Finding
**********************************************************************/
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE

Ogre::String bundlePath()
{
    char path[1024];
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    assert(mainBundle);

    CFURLRef mainBundleURL = CFBundleCopyBundleURL( mainBundle);
    assert(mainBundleURL);

    CFStringRef cfStringRef = CFURLCopyFileSystemPath( mainBundleURL, kCFURLPOSIXPathStyle);
    assert(cfStringRef);

    CFStringGetCString(cfStringRef, path, 1024, kCFStringEncodingASCII);

    CFRelease(mainBundleURL);
    CFRelease(cfStringRef);

    return Ogre::String(path);
}

#endif

	Main::Main()
	{
		#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
			Ogre::String mResourcePath;
			mResourcePath = bundlePath() + "/Contents/Resources/";
			mRoot = new Ogre::Root(mResourcePath + "plugins.cfg",
							   mResourcePath + "ogre.cfg", mResourcePath + "Ogre.log");
		#else
			mRoot = new Ogre::Root();
		#endif
	}

//----------------------------------------------//

	Main::~Main(){

		delete mRoot;
		mRoot = 0;
	}

//----------------------------------------------//

    bool Main::setResources(void)
    {
        // Load resource paths from config file
        Ogre::ConfigFile cf;

		#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
                Ogre::String mResourcePath;
                mResourcePath = bundlePath() + "/Contents/Resources/";
                cf.load(mResourcePath + "resources.cfg");
        #else
			cf.load("resources.cfg");
		#endif

        // Go through all sections & settings in the file
        Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

        Ogre::String secName, typeName, archName;
        while (seci.hasMoreElements())
        {
            secName = seci.peekNextKey();
            Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
            Ogre::ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i)
            {
                typeName = i->first;
                archName = i->second;
				#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
					// OS X does not set the working directory relative to the app,
					// In order to make things portable on OS X we need to provide
					// the loading with it's own bundle path location
					Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
						Ogre::String(bundlePath() + "/" + archName), typeName, secName);
				#else
					Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
						archName, typeName, secName);
				#endif
            }
        }
        Ogre::LogManager::getSingleton().logMessage( "Resource directories setup" );
		return true;
    }

//----------------------------------------------//

	bool Main::setConfiguration(void)
    {
        // Show the configuration dialog and initialise the system
        // You can skip this and use root.restoreConfig() to load configuration
        // settings if you were sure there are valid ones saved in ogre.cfg
        if(mRoot->showConfigDialog())
        {
            // If returned true, user clicked OK so initialise
            // Here we choose to let the system create a default rendering window by passing 'true'
            mRenderWindow = mRoot->initialise(true);
            return true;
        }
        else
        {
            return false;
        }
    }


//----------------------------------------------//

	bool Main::setLibs(){

		/**
		 * Set up GUI
		 */
		QuickGUI::registerScriptReader();

		/**
		 * Set up networking
		 */
		NetworkSystem::create("network.xml");

		return true;
	}

//----------------------------------------------//

	bool Main::createWindow(){
		mWindow = new TowerDefence( mRenderWindow );
		mWindow->start();
		return true;
	}

//----------------------------------------------//

	bool Main::setStartupResources(void)
	{
		// Initialise, parse all scripts etc
        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
		return true;
	}

//----------------------------------------------//

	void Main::go(void)
    {
		if ( !setResources() )
			return;

		if (!setConfiguration())
			return;

		if ( !setLibs() )
			return;

		if ( !setStartupResources() )
			return;

		if ( !createWindow() )
			return;

        mRoot->startRendering();
    }

//----------------------------------------------//


	TowerDefence::TowerDefence( Ogre::RenderWindow* w ):
	  Window(w)
    {
	}

//----------------------------------------------//

    TowerDefence::~TowerDefence()
    {
	}

//----------------------------------------------//

	Ogre::SceneManager * TowerDefence::createSceneManager(void)
    {
		return Ogre::Root::getSingleton().createSceneManager("TerrainSceneManager");
    }

//----------------------------------------------//

	Ogre::Camera * TowerDefence::createCamera(void)
    {
        // Create the camera
        Ogre::Camera * c = mSceneMgr->createCamera("PlayerCam");
		c->setPosition(700,300, 500);
		c->lookAt(600,80,600);
        c->setNearClipDistance(1);
		return c;
    }

//----------------------------------------------//

	Ogre::Viewport * TowerDefence::createViewport(void)
	{	// Create one viewport, entire window
		Ogre::Viewport* vp = mRenderWindow->addViewport(mCamera);
		vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
		// Alter the camera aspect ratio to match the viewport
		mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
		return vp;
	}

//----------------------------------------------//

	void TowerDefence::createScene(void)
    {
        // Set ambient light
		mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

		// Fog
        // NB it's VERY important to set this before calling setWorldGeometry
        // because the vertex program picked will be different
        Ogre::ColourValue fadeColour(0, 0, 0);
        mSceneMgr->setFog( Ogre::FOG_LINEAR, fadeColour, .001, 500, 1000);
        mRenderWindow->getViewport(0)->setBackgroundColour(fadeColour);

        std::string terrain_cfg("terrain.cfg");
        mSceneMgr->setWorldGeometry( terrain_cfg );
    }

	void TowerDefence::onExitClicked(const QuickGUI::EventArgs& event){
		this->close();
	}

//----------------------------------------------//

	void TowerDefence::final(void)
	{
		DefaultFrameListener * framelister = new DefaultFrameListener( mRenderWindow, mCamera, Ogre::Rect(500,0,mRenderWindow->getWidth(),mRenderWindow->getHeight()) );
		this->add((OIS::KeyListener*)framelister);
		this->add((OIS::MouseListener*)framelister);
		this->add((Ogre::FrameListener*)framelister);

		using namespace QuickGUI;
		Root::getSingleton().setDefaultFontName("micross.20");

		// Create Sheet
		SheetDesc* sd = DescManager::getSingleton().getDefaultSheetDesc();
		sd->widget_dimensions.size = Size(mRenderWindow->getWidth(),mRenderWindow->getHeight());
		mSheetFromFile = SheetManager::getSingleton().createSheet(sd);
		mGUIManager->setActiveSheet(mSheetFromFile);

		// create Main menu
		QuickGUI::ButtonDesc* singlePlayerBD = QuickGUI::DescManager::getSingleton().getDefaultButtonDesc();
		singlePlayerBD->button_imageName = "singleplayer.png";
		singlePlayerBD->widget_name = "SinglePlayer";
		singlePlayerBD->widget_dimensions.size = QuickGUI::Size(384,64);
		singlePlayerBD->widget_dimensions.position = QuickGUI::Point(50,50);
		singlePlayerBD->widget_dragable = false;
		mGUIManager->getActiveSheet()->createButton(singlePlayerBD);

		// create Main menu
		QuickGUI::ButtonDesc* exitBD = QuickGUI::DescManager::getSingleton().getDefaultButtonDesc();
		exitBD->button_imageName = "exit.png";
		exitBD->widget_name = "Exit";
		exitBD->widget_dimensions.size = QuickGUI::Size(384,64);
		exitBD->widget_dimensions.position = QuickGUI::Point(50,50 + 64 + 16);
		singlePlayerBD->widget_dragable = false;
		mGUIManager->getActiveSheet()->createButton(singlePlayerBD);

		/*TabControl* tc = mGUIManager->getActiveSheet()->createTabControl(Rect(275,75,250,250));
		tc->setTabReordering(true);
		Root::getSingleton().setDefaultColor(QuickGUI::ColourValue::Black);
		tc->createTabPage("Page 2");
		tc->createTabPage("Page 1",0);
		tc->createTabPageWithIcon("qgui.image.png","Page 3",0);
		tc->createTabPageWithIcon("qgui.image.png",0);
		Root::getSingleton().setDefaultColor(QuickGUI::ColourValue::White);

		PropertyGrid* propertyGrid = mGUIManager->getActiveSheet()->createPropertyGrid(Rect(550,75,250,300));
		PropertyGridSection* section1 = propertyGrid->createSection();
		section1->createTextProperty();
		PropertyGridSection* section2 = section1->createSection();
		section2->createTextProperty();
		section1->createBoolProperty();

		TreeView* treeView = mGUIManager->getActiveSheet()->createTreeView(Rect(0,75,200,300));
		TreeViewNode* level0Node = treeView->createNode("Node 0");

		for(int i = 1; i < 25; ++i)
		{
			treeView->createNode("Node " + Ogre::StringConverter::toString(i));
		}

		TreeViewNode* level1Node = level0Node->createNode("Node 2");
		TreeViewNode* level2Node = level1Node->createNode("Node 3");
		TreeViewNode* tvn = level0Node->createNode("Node 4");
		treeView->createNode("Node 5");

		TreeViewCheckBoxNode* tvcbn = treeView->createCheckBoxNode("Node 6");
		tvn = tvcbn->createNode("Node 7");
		tvn->createRadioButtonNode("Node 8");
		tvn->createRadioButtonNode("Node 9");

		// Create ToolBar with some Menus
		ToolBar* tb = mGUIManager->getActiveSheet()->createToolBar(Rect(0,560,200,20));
		Menu* filemenu = tb->createMenu("File");
		MenuItem * mi = filemenu->createTextItem("Exit");
		mi->addWidgetEventHandler(WIDGET_EVENT_MOUSE_CLICK,&TowerDefence::onExitClicked, this);

		Menu* m1 = tb->createMenu("Format");
		Menu* m2 = m1->createSubMenu("Word Wrap");
		Menu* m3 = m2->createSubMenu();
		m3->createTextItem();
		m3->setTextColor(QuickGUI::ColourValue::Green);

		// Create ComboBox with some items
		ComboBox* comboBox = mGUIManager->getActiveSheet()->createComboBox(Rect(325,50,150,20));
		comboBox->setMaxDropDownHeight(60);
		comboBox->setDropDownWidth(150);

		comboBox->createTextItem("CB Item 1");
		comboBox->createTextItem("CB Item 2");
		comboBox->createTextItem("CB Item 3",0);
		comboBox->createImageItem("qgui.image.png");

		// Create List with some items
		List* list = mGUIManager->getActiveSheet()->createList(Rect(300,450,200,100));
		list->setMultiSelect(true);

		list->createTextItem("Item 3");
		list->createTextItem("Item 2",0);
		list->createTextItem("Item 1",0);
		list->createTextItem("Item 5");
		list->createTextItem("Item 4",3);
		list->createImageItem("qgui.image.png");*/

	}
