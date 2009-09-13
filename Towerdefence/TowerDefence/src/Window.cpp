#include "Window.h"

#include "OgreParticleSystemManager.h"
#include "OgreMeshManager.h"

Window::Window(Ogre::RenderWindow* w ): 
	mRenderWindow(w)
	,mRequestClose(false)
{
	Ogre::Root::getSingleton().addFrameListener(this);
	Ogre::WindowEventUtilities::addWindowEventListener(mRenderWindow,this);
}

Window::~Window()
{
	//delete all entries in listeners
	for ( list<OIS::KeyListener*>::iterator i = this->mKeyListeners.begin(); i != this->mKeyListeners.end(); i++ ){
		delete (*i);
		*i = 0;		//set to null to prevent double delete (some listeres may be in other lists too!)
	}
	mKeyListeners.clear();

	for ( list<OIS::MouseListener*>::iterator i = this->mMouseListeners.begin(); i != this->mMouseListeners.end(); i++ ){
		delete (*i);
		*i = 0;
	}
	mMouseListeners.clear();

	for ( list<Ogre::FrameListener*>::iterator i = mFrameListeners.begin(); i != mFrameListeners.end(); i++ ) {
		delete (*i);
		*i = 0;
	}
	mFrameListeners.clear();

	//clean up GUI
	QuickGUI::Root::getSingletonPtr()->destroyGUIManager(mGUIManager);
	delete QuickGUI::Root::getSingletonPtr();

	//clean OI
	OIS::InputManager::destroyInputSystem(mInputManager);

	//clean up to lower layers
	Ogre::WindowEventUtilities::removeWindowEventListener(mRenderWindow,this);
	Ogre::Root::getSingleton().removeFrameListener(this);
}

void Window::start(){
	_initializeOIS();

	//main set up of ogre things
	mSceneMgr = this->createSceneManager();

	mCamera = this->createCamera();

	mViewport = this->createViewport();

	this->createScene();

	//set up GUI
	mGUIRoot = new QuickGUI::Root();
	QuickGUI::SkinTypeManager::getSingleton().loadTypes();
	QuickGUI::GUIManagerDesc d;
	mGUIManager = mGUIRoot->createGUIManager(d);

	this->final();
}

void Window::close(){
	mRequestClose = true;
}

void Window::add ( OIS::KeyListener * keylistener ){
	mKeyListeners.push_back (keylistener);
}

void Window::remove ( OIS::KeyListener * keylistener ){
	mKeyListeners.remove (keylistener);
}

void Window::add ( OIS::MouseListener * mouselistener ){
	mMouseListeners.push_back(mouselistener);
}

void Window::remove ( OIS::MouseListener * mouselistener ){
	mMouseListeners.remove(mouselistener);	
}

void Window::add ( Ogre::FrameListener * framelistener ){
	mFrameListeners.push_back(framelistener);
}

void Window::remove ( Ogre::FrameListener * framelistener ){
	mFrameListeners.remove(framelistener);
}

void Window::_initializeOIS()
{
	OIS::ParamList pl;	
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mRenderWindow->getCustomAttribute("WINDOW",&windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	//Default mode is foreground exclusive..but, we want to show mouse - so nonexclusive
	//pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	//pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));

	mInputManager = OIS::InputManager::createInputSystem( pl );

	//Create all devices
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

	mKeyboard->setEventCallback(this);
	mMouse->setEventCallback(this);

	//Set initial mouse clipping size
	mMouse->getMouseState().width = mRenderWindow->getWidth();
	mMouse->getMouseState().height = mRenderWindow->getHeight();
}

bool Window::keyPressed(const OIS::KeyEvent &arg)
{
	mGUIManager->injectChar(static_cast<Ogre::UTFString::unicode_char>(arg.text));
	mGUIManager->injectKeyDown(static_cast<QuickGUI::KeyCode>(arg.key));
	for ( list<OIS::KeyListener*>::iterator i = this->mKeyListeners.begin(); i != this->mKeyListeners.end(); i++ ){
		(*i)->keyPressed(arg);
	}
	return true;
}

bool Window::keyReleased(const OIS::KeyEvent &arg)
{
	mGUIManager->injectKeyUp(static_cast<QuickGUI::KeyCode>(arg.key));
	for ( list<OIS::KeyListener*>::iterator i = this->mKeyListeners.begin(); i != this->mKeyListeners.end(); i++ ){
		(*i)->keyReleased(arg);
	}
	return true;
}

bool Window::mouseMoved(const OIS::MouseEvent &arg)
{
	mGUIManager->injectMousePosition(arg.state.X.abs, arg.state.Y.abs);
	float z = arg.state.Z.rel;
	if(z != 0)
		mGUIManager->injectMouseWheelChange(z);

	for ( list<OIS::MouseListener*>::iterator i = this->mMouseListeners.begin(); i != this->mMouseListeners.end(); i++ ){
		(*i)->mouseMoved(arg);
	}
	return true;
}

bool Window::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	mGUIManager->injectMouseButtonDown(static_cast<QuickGUI::MouseButtonID>(id));
	for ( list<OIS::MouseListener*>::iterator i = this->mMouseListeners.begin(); i != this->mMouseListeners.end(); i++ ){
		(*i)->mousePressed(arg, id);
	}
	return true;
}

bool Window::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	mGUIManager->injectMouseButtonUp(static_cast<QuickGUI::MouseButtonID>(id));
	for ( list<OIS::MouseListener*>::iterator i = this->mMouseListeners.begin(); i != this->mMouseListeners.end(); i++ ){
		(*i)->mouseReleased(arg, id);
	}
	return true;
}

bool Window::frameStarted(const Ogre::FrameEvent& evt)
{
	for ( list<Ogre::FrameListener*>::iterator i = mFrameListeners.begin(); i != mFrameListeners.end(); i++ ) {
		if ( !(*i)->frameStarted(evt) )
			return false;
	}
	return true;
}

bool Window::frameEnded(const Ogre::FrameEvent& evt)
{
	for ( list<Ogre::FrameListener*>::iterator i = mFrameListeners.begin(); i != mFrameListeners.end(); i++ ) {
		if ( !(*i)->frameEnded(evt) )
			return false;
	}
	return true;
}

bool Window::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if ( mRequestClose )
		return false;

	if( mRenderWindow->isClosed() )
		return false;

	mKeyboard->capture();
	mMouse->capture();

	for ( list<Ogre::FrameListener*>::iterator i = mFrameListeners.begin(); i != mFrameListeners.end(); i++ ) {
		if ( !(*i)->frameRenderingQueued(evt) )
			return false;
	}
	return true;
}

void Window::windowResized(Ogre::RenderWindow* rw)
{
	mMouse->getMouseState().width = rw->getWidth();
	mMouse->getMouseState().height = rw->getHeight();
	mCamera->setAspectRatio(Ogre::Real(mCamera->getViewport()->getActualWidth()) / Ogre::Real(mCamera->getViewport()->getActualHeight()));
	mGUIManager->getActiveSheet()->redraw();
	mGUIManager->notifyViewportDimensionsChanged();
}
