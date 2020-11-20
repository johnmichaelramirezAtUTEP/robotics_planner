#include "Control/lego_control.h"
#include "Planning/planning.h"w
#include "Sensors/sensors.h"
#include "Planning/goalfinding.h"
#include "Planning/wander.h"
#include <ev3.h>

int main(void){
//	setupVariables();
//	initBoard();
//	addObstacles();
//	Node *backtrace = bfs();
//	printTrace(backtrace);
//	printBoard();
//	Instruction * instr = createInstructions();
//
//	setUpControl();
//
//	int i = 0;
//	while(instr[i].inst == 'f' || instr[i].inst == 'r'){
//		if(instr[i].inst == 'r'){
//			if(instr[i].value > 0){ //turn left
//				turnVehicleLeft();
//			}
//			else {//turn right
//				turnVehicleRight();
//			}
//		}
//		else if(instr[i].inst == 'f'){
//			goForward(instr[i].value);
//		}
//		i++;
//	}
	setUpSensors();
	TermPrintf("Color value: %i\n", readColorSensor());
	ButtonWaitForPress(BUTTON_ID_ENTER);
	TermPrintf("Sonar value: %i\n", readUltraSonicSensor());
	ButtonWaitForPress(BUTTON_ID_ENTER);
	int goal = goalfinding();
	while (!goal) {
		wander();
		wallfollow();
		goalfinding();
	}

	return 0;
}

