#ifndef DOOFRAND
#define DOOFRAND

class pendulum
{
public:
	pendulum();

	double getAngle(void) const;
	void update(void);
	void runSim(unsigned long int times);
private:
	double	l1;
	double	l2;//lengths
	double	m1;
	double	m2;	//masses
	double	O1, O2;	//angles
	double	w1, w2;	//angular velocities
	double	g;
	double	alfa1;
	double	alfa2;
	double	fps;
	double	dt;

};
int
genRand(void);

#endif // !1


