#include <math.h>
#include <ev3.h>
#include "control_setup.h"

#define TICKS_PER_METER 2050
#define MILLISECONDS_PER_90_TURN 1525

int prevEncoderTicksLeft = 0;
int prevEncoderTicksRight = 0;

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

void turnVehicleRightXDegrees(double degrees){
	OnFwdReg(OUT_A, 10);
	OnRevReg(OUT_D, 10);
	Wait(MILLISECONDS_PER_90_TURN * (degrees / 90.0));
	OutputStop(OUT_AD, true);
	return;
}

void turnVehicleLeftXDegrees(double degrees){
	OnFwdReg(OUT_D, 10);
	OnRevReg(OUT_A, 10);
	Wait(MILLISECONDS_PER_90_TURN * (degrees / 90.0));
	OutputStop(OUT_AD, true);
	return;
}

void goForward(double distance){
	int degreeOfRotation = (int)(distance * TICKS_PER_METER);
	RotateMotor(OUT_AD, 17, degreeOfRotation);
}

void goForwardNonBlocking(){
	OnFwdReg(OUT_AD, 17);
}

void goReverse(double distance){
	int degreeOfRotation = (int)(distance * TICKS_PER_METER);
	RotateMotor(OUT_AD, -10, degreeOfRotation);
}

void goReverseNonBlocking(){
	OnRevReg(OUT_AD, 10);
}

void stopVehicle(){
	OutputStop(OUT_AD, true);
}

int getRelativeEncoderTicksLeft(){
	return MotorRotationCount(OUT_A) - prevEncoderTicksLeft;
}

int getRelativeEncoderTicksRight(){
	return MotorRotationCount(OUT_D) - prevEncoderTicksRight;
}

void setRelativeEncoderValues(){
	prevEncoderTicksLeft = MotorRotationCount(OUT_A);
	prevEncoderTicksRight = MotorRotationCount(OUT_D);
}

