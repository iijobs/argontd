#include <Ogre.h>
#include <OgreTimer.h>

#include "DefaultFrameListener.h"
#include "TowerDefence.h"

DefaultFrameListener::DefaultFrameListener(Ogre::RenderWindow * renderwindow, Ogre::Camera * camera, const Ogre::Rect& mousearea)
        :
		mRenderwindow(renderwindow)
		,mCamera(camera)
        , mTranslateVector(Ogre::Vector3::ZERO)
        , mAvgFrameTime(0.1)
		, mQuit(false)
        , mRotX(0)
        , mRotY(0)
        , mUpdateMovement(false)
        , mProcessMovement(false)
        , mMoveFwd(false)
        , mMoveBck(false)
        , mMoveLeft(false)
        , mMoveRight(false)
		, mMouseArea(mousearea)
	{
	}
//--------------------------------------------------------------------------
    DefaultFrameListener::~DefaultFrameListener()
    {
		Ogre::Root::getSingleton().removeFrameListener(this);
    }

	//--------------------------------------------------------------------------
    bool DefaultFrameListener::frameRenderingQueued(const Ogre::FrameEvent& evt)
    {
		// update movement process
		if(mProcessMovement || mUpdateMovement)
		{
			mTranslateVector.x += mMoveLeft ? mAvgFrameTime * -MOVESPEED : 0;
			mTranslateVector.x += mMoveRight ? mAvgFrameTime * MOVESPEED : 0;
			mTranslateVector.z += mMoveFwd ? mAvgFrameTime * -MOVESPEED : 0;
			mTranslateVector.z += mMoveBck ? mAvgFrameTime * MOVESPEED : 0;

			mCamera->yaw(Ogre::Angle(mRotX));
			mCamera->pitch(Ogre::Angle(mRotY));
			mCamera->moveRelative(mTranslateVector);

			mUpdateMovement = false;
			mRotX = 0;
			mRotY = 0;
			mTranslateVector = Ogre::Vector3::ZERO;
		}


		//update mAvgFrameTime
		mAvgFrameTime = 1.0f/(mRenderwindow->getStatistics().avgFPS + 1.0f);
        if (mAvgFrameTime > 0.1f) mAvgFrameTime = 0.1f;

		return true;
    }

//--------------------------------------------------------------------------
    bool DefaultFrameListener::mouseMoved (const OIS::MouseEvent &e)
    {
		if ( e.state.X.abs < mMouseArea.left || e.state.X.abs > mMouseArea.right )
			return true;

		if ( e.state.Y.abs < mMouseArea.top || e.state.Y.abs > mMouseArea.bottom )
			return true;

		//if mousewheel moved -> ZOOM
		if ( e.state.Z.rel != 0 ){
			mTranslateVector.z +=  e.state.Z.rel * -2.0;
			mUpdateMovement = true;
		}

		//if LMB and NOT RMB ->  ROTATE
		if( e.state.buttonDown(OIS::MB_Left) && !e.state.buttonDown(OIS::MB_Right))
        {
 			mRotX += - e.state.X.rel * mAvgFrameTime * 10.0;
            mRotY += - e.state.Y.rel * mAvgFrameTime * 10.0;
            mUpdateMovement = true;
        }
		//IF RMB and NOT LMB
        else if( !e.state.buttonDown(OIS::MB_Left) && e.state.buttonDown(OIS::MB_Right) )
		{
            // translate camera
            mTranslateVector.x += e.state.X.rel * mAvgFrameTime * MOVESPEED;
            mTranslateVector.y += -e.state.Y.rel * mAvgFrameTime * MOVESPEED;
            mUpdateMovement = true;
        }
		//IF BOTH LMB and RMB
        else if( e.state.buttonDown(OIS::MB_Left) && e.state.buttonDown(OIS::MB_Right) )
        {
			// zoom
            mTranslateVector.z += e.state.X.rel + e.state.Y.rel * mAvgFrameTime * MOVESPEED;
            mUpdateMovement = true;
		}

        return true;
    }

//--------------------------------------------------------------------------
	bool DefaultFrameListener::keyPressed (const OIS::KeyEvent &e)
    {
		//if escape QUIT
		if (e.key == OIS::KC_ESCAPE) {
            mQuit = true;
            return false;
		} else {
			CheckMovementKeys( e.key, true );
		}

        return true;
    }

//--------------------------------------------------------------------------
    bool DefaultFrameListener::keyReleased (const OIS::KeyEvent &e)
    {
		CheckMovementKeys( e.key, false );
		return true;
    }

//--------------------------------------------------------------------------
	bool DefaultFrameListener::mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id)
    {
        return true;
	}

//--------------------------------------------------------------------------
	bool DefaultFrameListener::mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id)
    {
        return true;
    }

//--------------------------------------------------------------------------

	void DefaultFrameListener::CheckMovementKeys( const OIS::KeyCode& code , bool state )
    {
        switch ( code )
        {
			case OIS::KC_A:
                mMoveLeft = state;
                break;

            case OIS::KC_D:
                mMoveRight = state;
                break;

            case OIS::KC_S:
                mMoveBck = state;
                break;

            case OIS::KC_W:
                mMoveFwd = state;
                break;

            default:
                break;

        }
        mProcessMovement = mMoveLeft || mMoveRight || mMoveFwd || mMoveBck;
    }

