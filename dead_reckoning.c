#include "Control/lego_control.h"
#include "Planning/planning.h"
#include <ev3.h>

int main(void){
	setupVariables();
	initBoard();
	addObstacles();
	Node *backtrace = bfs();
	printTrace(backtrace);
	Instruction * instr = createInstructions();

	setUpControl();

	int i = 0;
	while(instr[i].inst == 'f' || instr[i].inst == 'r'){
		if(instr[i].inst == 'r'){
			if(instr[i].value > 0){ //turn right
				turnVehicleRight();
			}
			else {//turn left
				turnVehicleLeft();
			}
		}
		else if(instr[i].inst == 'f'){
			goForward(instr[i].value);
		}
		i++;
	}

	return 0;
}

