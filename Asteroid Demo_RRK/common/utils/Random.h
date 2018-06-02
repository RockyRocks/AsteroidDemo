#ifndef __RANDOM_H
#define __RANDOM_H

#include <time.h>

// parameters
#define CMATH_N 624
#define CMATH_M 397
#define CMATH_MATRIX_A 0x9908b0df   /* constant vector a */
#define CMATH_UPPER_MASK 0x80000000 /* most significant w-r bits */
#define CMATH_LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */   
#define CMATH_TEMPERING_MASK_B 0x9d2c5680
#define CMATH_TEMPERING_MASK_C 0xefc60000
#define CMATH_TEMPERING_SHIFT_U(y)  (y >> 11)
#define CMATH_TEMPERING_SHIFT_S(y)  (y << 7)
#define CMATH_TEMPERING_SHIFT_T(y)  (y << 15)
#define CMATH_TEMPERING_SHIFT_L(y)  (y >> 18)

// Random Description
//
// A random number generator based on the Mersenne Twister
// pseudorandom number generator.
class Random
{
public:
	Random();
	~Random();

	// Returns a number from 0 to n
	unsigned int random(unsigned int n);
	
	// Returns a new float between 0.0f - 1.0f
	float random();

	// Sets the seed
	void setRandomSeed(unsigned int n);

	// Get the seed
	unsigned int getRandomSeed();

	// Sets a random seed into generator
	void randomise();

private:
	unsigned int seed;
	unsigned int seed_sp;
	unsigned long mt[CMATH_N]; // the array for the state vector
	int mti; // mti==N+1 means that mt[N] is not initialised
};

#endif