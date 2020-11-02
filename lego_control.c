#include <math.h>
#include <ev3.h>

#define TICKS_PER_METER 1899

void turnVehicleRight(){
	int rotationCount = 0;
	int prevLeftTicks = MotorRotationCount(OUT_A); int prevRightTicks = MotorRotationCount(OUT_D);
	OnFwdReg(OUT_A, 10);
	OnRevReg(OUT_D, 10);
	while(rotationCount < 304){
		//left wheel rotates first so it will be ahead by 2-4 ticks, add 2 ticks to compensate
		rotationCount = abs(MotorRotationCount(OUT_A) - prevLeftTicks) + abs((MotorRotationCount(OUT_D) - prevRightTicks)) + 2;
	}
	OutputStop(OUT_AD, true);
	return;
}

void turnVehicleLeft(){
	int rotationCount = 0;
	int prevLeftTicks = MotorRotationCount(OUT_A); int prevRightTicks = MotorRotationCount(OUT_D);
	OnFwdReg(OUT_D, 10);
	OnRevReg(OUT_A, 10);
	while(rotationCount < 304){
		//right wheel rotates first so it will be ahead by 2-4 ticks, add 2 ticks to compensate
		rotationCount = abs(MotorRotationCount(OUT_D) - prevRightTicks) + abs((MotorRotationCount(OUT_A) - prevLeftTicks)) + 2;
	}
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
