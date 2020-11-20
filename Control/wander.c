#include <math.h>
#include <ev3.h>
#include "control_setup.h"
#include "goalfinding.h"

#define TICKS_PER_METER 2050
#define MILLISECONDS_PER_90_TURN 1550

void wander () {
	int color;
	int goalstatus = goalfinding();
	color = readColorSensor();
	while (color != 2 || goalstatus = 1) {
		goForward(.025);
		turnVehicledeg(10, 0);
	    goalstatus = goalfinding();
		color = readColorSensor();
	}

}
