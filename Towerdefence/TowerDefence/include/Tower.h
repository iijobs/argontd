#ifndef _TOWER_H_
#define _TOWER_H_

#include <list>
using std::list;

#include "ElementTypes.h"

namespace content {

class Tower
{
private:

	/**
	 * True if tower can attacks flying
	 */
	bool mAttackFlying;

	/**
	 * Element types of the damage
	 */
	list<ElementType> mElementTypes;

	/**
	 * The rate of which the tower attacks
	 */
	float mAttackrate;

	/**
	 * Base damage
	 */
	float mDamage;

	/**
	 * Current damage ( => base damage amplified with bufs)
	 */
	float mCurrentDamage;

public:
	Tower(void);

	virtual ~Tower(void);
};

}

#endif