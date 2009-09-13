#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <list>
using std::list;

#include <OgreEntity.h>
#include <OgreRenderSystem.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreStringConverter.h>
#include <OgreWindowEventUtilities.h>

#include <OIS/OIS.h>

#include <QuickGUI.h>

class Window :
	public Ogre::FrameListener,
	public Ogre::WindowEventListener,
	public OIS::KeyListener,
	public OIS::MouseListener
{
public:

	/**
	 * Constructor
	 * @param Ogre::RenderWindow *
	 */
	Window(Ogre::RenderWindow* w);

	virtual ~Window();

	/**
	 * Start the application
	 */
	void start();

	/**
	 * Close the application
	 */
	void close();

	/**
	 * Register an OIS::KeyListener, will be deleted when windows destructor is ran
	 * @param keylistener
	 */
	void add ( OIS::KeyListener * keylistener );

	/**
	 * Deregister an OIS::KeyListener
	 * @param keylistener
	 */
	void remove ( OIS::KeyListener * keylistener );

	/**
	 * Register an OIS::MouseListener, will be deleted when windows destructor is ran
	 * @param mouselistener
	 */
	void add ( OIS::MouseListener * mouselistener );

	/**
	 * Deregister an OIS::MouseListener
	 * @param mouselistener
	 */
	void remove ( OIS::MouseListener * mouselistener );

	/**
	 * Register an Ogre::FrameListener, will be deleted when windows destructor is ran
	 * @param framelistener
	 */
	void add ( Ogre::FrameListener * framelistener );

	/**
	 * Deregister an Ogre::FrameListener
	 * @param framelistener
	 */
	void remove ( Ogre::FrameListener * framelistener );

	/**
	 * Create a scenemanager
	 * @return Ogre::SceneManager *
	 */
	virtual Ogre::SceneManager * createSceneManager() = 0;

	/**
	 * Create a camera
	 * @return Ogre::Camera *
	 */
	virtual Ogre::Camera * createCamera() = 0;

	/**
	 * Create a viewport
	 * @return Ogre::Viewport *
	 */
	virtual Ogre::Viewport * createViewport() = 0;

	/**
	 * Create initial scene
	 */
	virtual void createScene() = 0;

	/**
	 * Called after creation of scene, can be used to create GUI, attach frame/key/mouse listeners etc
	 */
	virtual void final() = 0;

private:

	/* KeyListener Callbacks */
	bool keyPressed(const OIS::KeyEvent &arg);
	bool keyReleased(const OIS::KeyEvent &arg);

	/* MouseListener Callbacks */
	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	/* Window Event Callbacks */
	void windowResized(Ogre::RenderWindow* rw);

	/* FrameEvent Callbacks */
    bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);

protected:

	/**
	 * List with all keylisteners, needed because OIS only supports one listener we need to broadcast ourselfs
	 */
	list<OIS::KeyListener*>		mKeyListeners;

	/**
	 * List with all mouselistener, needed because OIS only supports one listener we need to broadcast ourselfs
	 */
	list<OIS::MouseListener*>	mMouseListeners;

	/**
	 * List with all framelisteners
	 */
	list<Ogre::FrameListener*>	mFrameListeners;

	//OGRE LOWLEVEL
	Ogre::RenderWindow*			mRenderWindow;
	bool mRequestClose;

	//OGRE CAMERA
	Ogre::Viewport *			mViewport;
	Ogre::Camera*				mCamera;

	//OGRE HIGH LEVEL
	Ogre::SceneManager *		mSceneMgr;
	Ogre::SceneNode *			mMainNode;

	//IO
	OIS::InputManager*			mInputManager;
	OIS::Keyboard*				mKeyboard;
	OIS::Mouse*					mMouse;

	//GUI
	QuickGUI::Root*				mGUIRoot;
	QuickGUI::GUIManager*		mGUIManager;

private:
	void _initializeOIS();

};

#endif
