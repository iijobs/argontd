#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <ctime> 
#include <cstdlib>

class Random {

private:

	/**
	 *	return a random value between 0 and 1 distributed on a uniform way
	 */
	float random(){
		return (float)rand()/(float)RAND_MAX;
	}

public:

	Random(){
		srand((unsigned)time(0)); 
	}

	float next( float min, float max )  
	{ 	    
		return min + random() * (max-min);
	}
};



#endif