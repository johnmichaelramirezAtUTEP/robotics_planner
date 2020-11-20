#include <math.h>
#include <ev3.h>
#include "control_setup.h"
#include "goalfinding.h"
#include "lego_control.h"
#include "../Sensors/sensors.h"

#define TICKS_PER_METER 2050
#define MILLISECONDS_PER_90_TURN 1550

void wander () {
	int color;
	int goalstatus = goalfinding();
	color = readColorSensor();
	while (color != 2) {
		goForward(.05);
		turnVehicledeg(7, 1);
	    goalstatus = goalfinding();
		color = readColorSensor();


		if(ButtonIsDown(BTNLEFT)) {
			exit(0);
		}
	}

}
