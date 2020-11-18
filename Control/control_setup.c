#include <ev3.h>

void setup(){
	//initialize output
	OutputInit();
	if(OutputInitialized()){
		TermPrintf("Output Initialized!\n");
	}
	else {
		TermPrintf("Unable to initialize output.\n");
		exit(0);
	}

	//setup tachometers in motors
	if(OutputSetType(OUT_A, DEVICE_TYPE_TACHO) && OutputSetType(OUT_D, DEVICE_TYPE_TACHO)){
		TermPrintf("Device type set!\n");
	}
	else {
		TermPrintf("Unable to set device type.\n\n");
		exit(0);
	}

	//reset ticks
	ResetRotationCount(OUT_A); ResetRotationCount(OUT_D);
}
