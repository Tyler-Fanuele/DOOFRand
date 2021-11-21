/*
* 
*/

#include <cmath>
#include <iostream>
#include "doofrand.hpp"
#include <ctime>

#define M_PI  3.141592653589793238462643383279502884197169399375105820974944592307816
using namespace std;

pendulum::pendulum()
{
	l1 = time(NULL);
	l2 = 190.0;
	m1 = 1.0055;
	m2 = time(NULL) / 10.0;
	O1 = (time(NULL) / 200.0) * M_PI / 2.0;
	O2 = 2.0 * M_PI / 3.0;
	w1 = 0.0;
	w2 = 0.0;
	fps = 3000.0;
	dt = 1.0 / fps;
	g = 9.01;
}

double 
pendulum::getAngle(void) const
{
	return w2;
}

void 
pendulum::update(void)
{
	alfa1 = (-g * (2 * m1 + m2) * sin(O1) - g * m2 * sin(O1 - 2 * O2) - 2 * m2 * sin(O1 - O2) *
		(w2 * w2 * l2 + w1 * w1 * l1 * cos(O1 - O2))) / (l1 * (2 * m1 + m2 - m2
			* cos(2 * O1 - 2 * O2))),
		alfa2 = (2 * sin(O1 - O2)) * (w1 * w1 * l1 * (m1 + m2) + g * (m1 + m2)
			* cos(O1) + w2 * w2 * l2 * m2 * cos(O1 - O2)) / l2 / (2 * m1 + m2 - m2
				* cos(2 * O1 - 2 * O2));

	w1 += 10 * dt * alfa1;
	w2 += 10 * dt * alfa2;
	O1 += 10 * dt * w1;
	O2 += 10 * dt * w2;
}

void 
pendulum::runSim(unsigned long int times)
{
	l1 = time(NULL);
	m2 = time(NULL) / 10.0;
	O1 = (time(NULL) / 200.0) * M_PI / 2.0;
	for (int i = 0; i < times; i++)
	{
		update();
	}
}

union Unit
{
	long int Int;
	double Float;
};

unsigned long int SEED = static_cast<unsigned long int>(time(NULL)) % 100;

int
genRand(void)
{
	pendulum random;
	Unit unit; 
	random.runSim(SEED);
	unit.Float = random.getAngle() * 1000000000000000;
	if (SEED < 300)
	{
		if (SEED % 2)
		{
			SEED = SEED + 1;
		}
		else
		{
			SEED = SEED + 5;
		}
	}
	else
	{
		SEED = SEED % 300;
		SEED += 10;
	}
	return abs(unit.Int) % 32768;
}