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
	int read = ReadSensor(IN_2);
	TermPrintf("Color value: %i\n", read);
	return read;
}

int readUltraSonicSensor(){
	int read = ReadSensor(IN_3);
		TermPrintf("Sonar value: %i\n", read);
		return read;
}
