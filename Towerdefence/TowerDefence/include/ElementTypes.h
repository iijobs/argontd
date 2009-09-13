#ifndef _DAMAGETYPES_H_
#define _DAMAGETYPES_H_

namespace content {

/**
 * An enumeration of all element types
 */
class ElementTypes {

public:

	/**
	 * Normal damage
	 */
	static const int Normal = 0;

	/**
	 * Fire damage: burns over time. Extra damage against frost creatures
	 */
	static const int Fire = 1;

	/**
	 * Frost damage: slows. Extra damage against fire creatures.
	 */
	static const int Frost = 2;

	/**
	 * Poison damage: slows + damage over time. Extra damage against human, mechanic ignore this
	 */
	static const int Poison = 3;

	/**
	 * Shock damage: stuns. Extreme extra damage against mechanic
	 */
	static const int Shock = 4;
};

typedef int ElementType;

}

#endif
