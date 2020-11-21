#include <math.h>
#include <ev3.h>
#include "control_setup.h"
#include "lego_control.h"
#include "../Sensors/sensors.h"
int goalfinding() {
   int distTraveled = 0;
   int color = 0;
   int distance = readUltraSonicSensor();

	if (distance <= 30 && distance >= 1) {
		while (color != 2 && distTraveled < distance) {
			goForward (.01);
			distTraveled += .01;
			color = readColorSensor();
			if(color == 2) {
				return 0;
			}
		}
		return 1;
	}

   return 0;
}


int goalfindingspin() {
   int distTraveled = 0;
   int color = 0;
   int distance = readUltraSonicSensor();
   int i = 0;

   for (i = 0; i <= 36; i++) {
	turnVehicledeg(10, 1);
	if (distance <= 30 && distance >= 1) {
		while (color != 2 && distTraveled < distance) {
			goForward (.01);
			distTraveled += .01;
			color = readColorSensor();
			if(color == 2) {
				return 0;
			}
		}
		return 1;
	}
   }

   return 0;
}
