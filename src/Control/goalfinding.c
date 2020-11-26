#include <math.h>
#include <ev3.h>
#include "control_setup.h"
#include "lego_control.h"
#include "../Sensors/sensors.h"
#include "wander.h"

int goalfinding() {
   int distance = readUltraSonicSensor();
	if (distance <= 40 && distance >= 1) {
		SoundInit();
		if(SoundInitialized()){
			PlayTone(2000, 10000);
		}
		TermPrintf("Annihilating Goal\n");
		goForward ((distance+50)/100.0);
		TermPrintf("Goal annihilated\n");
		return 1;
	}

   return 0;
}


int goalfindingspin() {
   int i = 0;
   for (i = 0; i < 36; i++) {
	   TermPrintf("Turning 14 degrees\n");
	   turnVehicleLeftXDegrees(14.0);
	   if(goalfinding()){
		   return 1;
	   }
   }

   return 0;
}
