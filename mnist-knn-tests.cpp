/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Tests for the MNISTImage classes
 *
 */

#include <cassert>
#include <cmath>
using namespace std;

#include "MNISTImageImpls.h"

int main(int argc, char** argv)
{
	uint8 a0[3]={0,0,0};
	uint8 a1[3]={1,1,1};

	FullArrayMNISTImage fai0(a0, 3, 0);
	FullArrayMNISTImage fai1(a1, 3, 0);

	assert(fai0.distance(&fai1) == sqrt(3));
	assert(fai1.distance(&fai0) == sqrt(3));
	assert(fai0.distance(&fai0) == 0.0);
	assert(fai1.distance(&fai1) == 0.0);

	SumMNISTImage si0(a0, 3, 0);
	SumMNISTImage si1(a1, 3, 0);

	assert(si0.distance(&si1) == 3.0);
	assert(si1.distance(&si0) == 3.0);
	assert(si0.distance(&si0) == 0.0);
	assert(si1.distance(&si1) == 0.0);
}
