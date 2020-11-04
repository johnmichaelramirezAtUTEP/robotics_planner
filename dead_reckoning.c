#include "Control/control_setup.h"
#include "Control/lego_control.h"
#include "Planning/planning.h"

int main(void){
	setupVariables();
	initBoard();
	addObstacles();
	printBoard();
	Node *backtrace = bfs();
	printTrace(backtrace);
//	printBoard();
//	createInstructions();
	return 0;
}

