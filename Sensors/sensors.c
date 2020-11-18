#include <ev3_sensor.h>
#include <ev3_constants.h>
#include <ev3.h>


void setUpSensors(){
	SensorsInit();
	if(SensorsInitialized()){
		TermPrintf("Sensors Initialized!\n");
	}
	else {
		TermPrintf("Unable to initialize sensors.\n");
	}

	SetAllSensorMode(NO_SEN, COL_COLOR, US_DIST_CM, NO_SEN);
}

int readColorSensor(){
	return ReadSensor(IN_2);
}

int readUltraSonicSensor(){
	return ReadSensor(IN_3);
}
