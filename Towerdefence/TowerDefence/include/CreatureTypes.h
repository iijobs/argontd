#ifndef _CREATURETYPES_H_
#define _CREATURETYPES_H_

namespace content {

/**
 * An enumeration of all types of creatures
 */
class CreatureTypes {

public:

	/**
	 * Weak to poison
	 */
	static const int Human = 0;

	/**
	 * Weak to shock
	 */
	static const int Mechnanic = 1;

	/**
	 * Semi-Immune to all (super creatures)
	 */
	static const int Alien = 2;
};

typedef int CreatureType;

class CreatureElementTypes {

public:

	/**
	 * Normal damage, no bonusses
	 */
	static const int Normal = 0;

	/**
	 * Fire, weak agains frost, immune to fire
	 */
	static const int Fire = 1;

	/**
	 * Frost, weak against fire, immune to frost
	 */
	static const int Frost = 2;
};

typedef int CreatureElementType;

}

#endif