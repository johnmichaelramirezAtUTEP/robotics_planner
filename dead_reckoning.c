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

	int size = (int) instr[0].value;

	setUpControl();

	int i = 0;;
	for(;i < size; i++){
//		if(instr[i].inst == 'r'){
//			if(instr[i].value > 0){ //turn right
//				turnVehicleRight();
//			}
//			else {//turn left
//				turnVehicleLeft();
//			}
//		}
//		else if(instr[i].inst == 'f'){
//			goForward(instr[i].value);
//		}
		if(i % 5 == 0){
			ButtonWaitForPress(BUTTON_ID_ENTER);
		}
		TermPrintf("Inst: %c\n", instr[i].inst);
	}
	ButtonWaitForPress(BUTTON_ID_ENTER);

	return 0;
}

