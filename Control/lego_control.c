#include <math.h>
#include <ev3.h>
#include "control_setup.h"

#define TICKS_PER_METER 2050
#define MILLISECONDS_PER_90_TURN 1550

void setUpControl(){
	setup();
}

void turnVehicleRight(){
	OnFwdReg(OUT_A, 10);
	OnRevReg(OUT_D, 10);
	Wait(MILLISECONDS_PER_90_TURN);
	OutputStop(OUT_AD, true);
	return;
}

void turnVehicleLeft(){
	OnFwdReg(OUT_D, 10);
	OnRevReg(OUT_A, 10);
	Wait(MILLISECONDS_PER_90_TURN);
	OutputStop(OUT_AD, true);
	return;
}

void goForward(double distance){
	int degreeOfRotation = (int)(distance * TICKS_PER_METER);
	RotateMotor(OUT_AD, 10, degreeOfRotation);
}

void goReverse(double distance){
	int degreeOfRotation = (int)(distance * TICKS_PER_METER);
	RotateMotor(OUT_AD, -10, degreeOfRotation);
}
