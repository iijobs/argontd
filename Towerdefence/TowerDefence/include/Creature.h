#ifndef _CREATURE_H_
#define _CREATURE_H_

#include <list>
using std::list;

#include "CreatureTypes.h"

namespace content {

class Creature
{
private:

	/**
	 * True if creature can fly
	 */
	bool isFlying;

	/**
	 * Normal speed without any effects
	 */
	float mNormalSpeed;

	/**
	 * Current speed, after applying slow/speed effects
	 */
	float mCurrentSpeed;

	/**
	 * Maximum/Start HP
	 */
	int mMaxHP;

	/**
	 * Current HP
	 */
	int mCurrentHP;

	/**
	 * Type of creature: human/mechanic/alien
	 */
	CreatureType mType;

	/**
	 * Element types: normal, fire, frost
	 */
	list<CreatureElementType> mElementTypes;

public:

	Creature(void);

	~Creature(void);
};

}

#endif
