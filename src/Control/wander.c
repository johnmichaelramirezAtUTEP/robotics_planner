#include <math.h>
#include <ev3.h>
#include "control_setup.h"
#include "goalfinding.h"
#include "lego_control.h"
#include "../Sensors/sensors.h"

#define TICKS_PER_METER 2050
#define MILLISECONDS_PER_90_TURN 1550

int wander () {
	int color = 0, count = 0;
	int goalstatus = goalfinding();
	color = readColorSensor();
	while (color != 2 && !goalstatus) {
		goForward(.05);
		turnVehicledeg(7, 1);

		color = readColorSensor();

		goalstatus = goalfinding();

		if(ButtonIsDown(BTNLEFT)) {
			exit(0);
		}

		if(count == 10) {
			goalstatus = goalfindingspin();
			count = 0;
		}
		count++;
	}

	if (goalstatus) {
		return 1;
	} else {
		return 0;
	}

}
