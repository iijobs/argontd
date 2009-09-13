#ifndef _TERRAINFRAMELISTENER_H_
#define _TERRAINFRAMELISTENER_H_

#include <OGRE/Ogre.h>
#include <OGRE/OgreFrameListener.h>
#include <OIS/OIS.h>

class TowerDefence;

/**
 *	Default frame listener provides a free camera, movement keys and esc -> exit
 */
class DefaultFrameListener : OIS::KeyListener, OIS::MouseListener, Ogre::FrameListener
{
    #define MINSPEED .150f
    #define MOVESPEED 15
    #define MAXSPEED 1.800f

    protected:

		Ogre::RenderWindow * mRenderwindow;
		Ogre::Camera * mCamera;

		Ogre::Vector3 mTranslateVector;
		float mAvgFrameTime;

		/**
		 * The quit flag
		 */
        bool mQuit;

		//mouse moved
		float mRotX, mRotY;
        bool mUpdateMovement;

		//movement keys pressed
		bool mProcessMovement;
        bool mMoveFwd;
        bool mMoveBck;
        bool mMoveLeft;
        bool mMoveRight;

        Ogre::Rect mMouseArea;

    public:
		DefaultFrameListener(Ogre::RenderWindow * renderwindow, Ogre::Camera * camera, const Ogre::Rect& mousearea);

        virtual ~DefaultFrameListener();

    private:

		/**
		 * Captures mouse movement using OIS
		 */
		virtual bool mouseMoved(const OIS::MouseEvent &e);
		virtual bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
        virtual bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

		/**
		 * Captures key event using OIS
		 */
        virtual bool keyPressed(const OIS::KeyEvent &e);
        virtual bool keyReleased(const OIS::KeyEvent &e);

		void CheckMovementKeys( const OIS::KeyCode& code , bool state );

        /**
		 * Event handlers
		 */
        bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    };


#endif
