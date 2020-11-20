#include <math.h>
#include <ev3.h>
#include "control_setup.h"
#include "lego_control.h"
#include "../Sensors/sensors.h"
int goalfinding() {
   int distance = readUltraSonicSensor();

	if (distance <= 10 && distance >= 1) {
		goForward (distance+2);
		return 1;
	} else {
		return 0;
	}
}
