#include "Control/lego_control.h"
#include "Planning/planning.h"
#include "Sensors/sensors.h"
#include "Control/goalfinding.h"
#include "Control/wander.h"
#include <ev3_sound.h>
#include <ev3.h>

void wallfollow(void);

int main(void){
	setUpSensors();
	int goal = goalfinding();
	while (!goal) {
		TermPrintf("Wandering Start\n");
		goal = wander();
		if(goal) {
			exit(0);
		}
		TermPrintf("Wandering End\n");
		TermPrintf("Wall Follow Start\n");
		wallfollow();
		TermPrintf("Wall Follow End\n");
		turnVehicleRightXDegrees(135.0);
		goal = goalfinding();
		if(ButtonIsDown(BTNLEFT)){
			exit(0);
		}
	}

	return 0;
}

void wallfollow(){
	int wallFollowing = 1;
	int distanceTraveled = 0;
	int missed = 0;
	turnVehicleRightXDegrees(30.0);
	while(wallFollowing){
		setRelativeEncoderValues();
		goForwardNonBlocking();
		while((getRelativeEncoderTicksLeft() + getRelativeEncoderTicksRight())/2 < 256){
			if(goalfinding()){
				exit(0);
			}
			if(countColor() == 15){
				stopVehicle();
				goReverseNonBlocking();
				Wait(500);
				stopVehicle();
				turnVehicleRightXDegrees(20.0);
				goForwardNonBlocking();
			}
		}

		distanceTraveled += 1;
		stopVehicle();
		turnVehicleLeftXDegrees(90.0);
		if(countColor() == 15){
			turnVehicleRightXDegrees(90.0);
			missed = 0;
		}
		else {
			missed++;
		}

		if(distanceTraveled % 8 == 0){
			if(goalfindingspin()){
				exit(0);
			}
		}
		if(distanceTraveled >= 32 || missed == 4){
			wallFollowing = 0;
		}
	}
	return;
}

