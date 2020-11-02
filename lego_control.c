#include <math.h>
#include <ev3.h>

#define PI 3.1415926535
#define TICKS_PER_METER 1899

void turnVehicleRight(double degrees){
	int rotationCount = 0;
	int prevLeftTicks = MotorRotationCount(OUT_A); int prevRightTicks = MotorRotationCount(OUT_D);
	OnFwdReg(OUT_A, 10);
	OnRevReg(OUT_D, 10);
	while(rotationCount < 304){
		//right wheel rotates first so it will be ahead by 2-4 ticks, add 2 ticks to compensate
		rotationCount = (MotorRotationCount(OUT_A) - prevLeftTicks) + abs((MotorRotationCount(OUT_D) - prevRightTicks)) + 2;
	}
	OutputStop(OUT_AD, true);
	return;
}

void turnVehicleLeft(double degrees){
	int rotationCount = 0;
	int prevLeftTicks = MotorRotationCount(OUT_A); int prevRightTicks = MotorRotationCount(OUT_D);
	OnFwdReg(OUT_D, 10);
	OnRevReg(OUT_A, 10);
	while(rotationCount < 304){
		//right wheel rotates first so it will be ahead by 2-4 ticks, add 2 ticks to compensate
		rotationCount = (MotorRotationCount(OUT_D) - prevRightTicks) + abs((MotorRotationCount(OUT_A) - prevLeftTicks)) + 2;
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

int main(void)
{
	//initialize output
	OutputInit();
	if(OutputInitialized()){
		TermPrintf("Output Initialized!\n");
	}
	else {
		TermPrintf("Unable to initialize output.\n");
	}

	//setup tachometers in motors
	if(OutputSetType(OUT_A, DEVICE_TYPE_TACHO) && OutputSetType(OUT_D, DEVICE_TYPE_TACHO)){
		TermPrintf("Device type set!\n");
	}
	else {
		TermPrintf("Unable to set device type.\n\n");
	}

	//reset ticks
	ResetRotationCount(OUT_A); ResetRotationCount(OUT_D);

//	turnVehicleLeft(0.0);
//	turnVehicleRight(0.0);
//	goForward(1.0);
//	goReverse(1.0);
	return 0;
}
