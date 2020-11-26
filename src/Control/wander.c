#include <math.h>
#include <ev3.h>
#include "control_setup.h"
#include "goalfinding.h"
#include "lego_control.h"
#include "../Sensors/sensors.h"

#define TICKS_PER_METER 2050
#define MILLISECONDS_PER_90_TURN 1550

int countColor(){
	int colorCount = 0;
	int i;
	for(i = 0; i < 3; i++){
		if(readColorSensor() <= 15){
			colorCount++;
		}
		Wait(25);
	}
	if(colorCount >= 2){
		return 15;
	}
	else {
		return 100;
	}
}

int wander () {
	int color = 0, count = 0;
	int goalstatus = goalfinding();
	color = countColor();
	while (color != 20 && !goalstatus) {
		goForward (.025);
		color = countColor();
		if(color == 15){
			return 0;
		}
		goForward (.025);
		turnVehicleLeftXDegrees(7.0);

		color = countColor();

		goalstatus = goalfinding();

		if(ButtonIsDown(BTNLEFT)) {
			exit(0);
		}

		if(count == 10) {
			TermPrintf("Goal Finding Spin\n");
			goalstatus = goalfindingspin();
			TermPrintf("Goal Spin End\n");
			count = 0;
		}
		count++;
	}

	if (goalstatus) {
		TermPrintf("Goal covered\n");
		return 1;
	} else {
		TermPrintf("Goal not covered\n");
		return 0;
	}

}
