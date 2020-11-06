#include <ev3.h>
#include <math.h>
#include <stdlib.h>
//Testing only
#include <unistd.h>
#include <stdio.h>
//
#include "parameters.h"
#include "planning.h"

#define WIDTH 16
#define HEIGHT 10
#define MWIDTH 4.88
#define MHEIGHT 3.05
#define SQUARE .305

int Board[WIDTH][HEIGHT];
int Gx, Gy;
int Sx, Sy;

int visited[WIDTH][HEIGHT];
int found;

double moves_b[90][2];
double moves[90][2];
int num_moves;


void setupVariables(){
	memset(visited, 0, sizeof(visited[0][0]) * HEIGHT * WIDTH);
	found = 0;
}

void printBoard () {
	int i, j;
	for (i = HEIGHT-1; i >= 0; i--) {
		TermPrintf("%d",i);
		for(j = 0; j < WIDTH; j++) {
			TermPrintf("%c",Board[i][j]);
		}
		TermPrintf("%c",'\n');
	}
	TermPrintf(" 01234567890123456\n");
	ButtonWaitForPress(BUTTON_ID_ENTER);
}

void addObstacle(double x, double y) {
  if (x != -1 && y != -1) {
    int height = (int) ((y / SQUARE) + .5);
    int width = (int) ((x / SQUARE) + .5);
    Board[height][width] = 'B';
  }
}

void addObstacles() {
	int i;
  for(i = 0; i < MAX_OBSTACLES; i++)
      addObstacle(obstacle[i][0],obstacle[i][1]);
}

void initBoard() {
	int i,j;
	for (i = 0; i < HEIGHT; i++) {
		for(j = 0; j < WIDTH; j++) {
			Board[i][j] =  '-';
		}
	}

  Sx = ((start[0] / SQUARE) + .5);
  Sy = ((start[1] / SQUARE) + .5);

  Gx = ((goal[0] / SQUARE) + .5);
  Gy = ((goal[1] / SQUARE) + .5);

  Board[Sy][Sx] = 'S';
  Board[Gy][Gx] = 'G';

  addObstacles();
}

double distance(int x1, int x2, int y1, int y2){
  return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

void sort(Direction dists[4]){
  int min_ind,i,j;
  for(i=0; i<4; i++){
    min_ind = i;
    for(j=i+1; j<4; j++)
      if(dists[j].dist < dists[min_ind].dist)
        min_ind=j;
      Direction temp = dists[i];
      dists[i] = dists[min_ind];
      dists[min_ind] = temp;
  }
}

void initNode(Node *self, int x, int y, Node *parent, Node *next){
	self->x = x;
	self->y = y;
	self->parent = parent;
	self->next = next;
}

Node * bfs(){
	//queue
	Node *head = malloc(sizeof(Node));
	initNode(head, Sx, Sy, NULL, NULL);
	Node *tail = head;
	//add start to queue
	//while queue not empty
	while(head != NULL){
		Node *current = head;

		//if at goal, backtrace
		if(current->x == Gx && current->y == Gy){
			TermPrintf("Goal found -> x:%d, y:%d\n", current->x, current->y);
			ButtonWaitForPress(BUTTON_ID_ENTER);
			return current;
		}

		//add all legal locations to end of queue
		int x = current->x, y = current->y, i;
		int directions [4][2] = {{x-1, y},{x+1, y},{x, y+1},{x, y-1}};
		for(i=0; i<4; i++){
			int xx = directions[i][0];
			int yy = directions[i][1];
			if(xx>=0 && xx<16 && yy>=0 && yy<10 && Board[yy][xx]!='B' && visited[xx][yy] == 0){
//				if(xx==6 && yy==4){
//					TermPrintf("adding blocked %c\n", Board[yy][xx]);
//				}
				visited[xx][yy] = 1;
				Node *to_add = malloc(sizeof(Node));
				initNode(to_add, xx, yy, current, NULL);
				tail->next = to_add;
				tail = tail->next;
			}
		}

		//increment queue pointer
		head = head->next;
	}
	return NULL;
}

void setInstruction(Instruction *inst, char c, double value){
	inst->inst = c;
	inst->value = value;
}

void printTrace(Node *goal){
	int i=0;
	while(goal != NULL){
//		TermPrintf("%d, %d\n", goal->x, goal->y);
		moves_b[i][0] = goal->x;
		moves_b[i][1] = goal->y;
		Board[goal->y][goal->x] = '*';
		goal = goal->parent;
		i++;
	}
	num_moves = i-1;

	int j;
	for(j = i-1; j>=0; j--){
		moves[i-1-j][0] = moves_b[j][0];
		moves[i-1-j][1] = moves_b[j][1];
	}

//	for(j=0; j<i; j++){
//		TermPrintf("%f %f\n", moves[j][0], moves[j][1]);
//	}
}

Instruction * createInstructions(){
	Instruction * instr = malloc(sizeof(Instruction) * 180);
	instr[0].inst = 'x';instr[0].value = -1.0;
	int ox = 1, oy = 0, i;
	int ip = 0;
	
	for(i=0; i<num_moves; i++){
		int dx = moves[i+1][0] - moves[i][0];
		int dy = moves[i+1][1] - moves[i][1];
		
		if(ox==0 && oy==1){
			if(dx==0 && dy==1){
			}
			else if(dx==0 && dy==-1){
				setInstruction(instr+ip, 'r', 90);
				ip ++;
				setInstruction(instr+ip, 'r', 90);
				ip ++;
			}
			else if(dx==1 && dy==0){
				setInstruction(instr+ip, 'r', -90);
				ip ++;
			}
			else if(dx==-1 && dy==0){
				setInstruction(instr+ip, 'r', 90);
				ip ++;
			}
		}
		else if(ox==0 && oy==-1){
			if(dx==0 && dy==1){
				setInstruction(instr+ip, 'r', 90);
				ip ++;
				setInstruction(instr+ip, 'r', 90);
				ip ++;
			}
			else if(dx==0 && dy==-1){
			}
			else if(dx==1 && dy==0){
				setInstruction(instr+ip, 'r', 90);
				ip ++;
			}
			else if(dx==-1 && dy==0){
				setInstruction(instr+ip, 'r', -90);
				ip ++;
			}
		}
		else if(ox==1 && oy==0){
			if(dx==0 && dy==1){
				setInstruction(instr+ip, 'r', 90);
				ip ++;
			}
			else if(dx==0 && dy==-1){
				setInstruction(instr+ip, 'r', -90);
				ip ++;
			}
			else if(dx==1 && dy==0){
			}
			else if(dx==-1 && dy==0){
				setInstruction(instr+ip, 'r', 90);
				ip ++;
				setInstruction(instr+ip, 'r', 90);
				ip ++;
			}
		}
		else if(ox==-1 && oy==0){
			if(dx==0 && dy==1){
				setInstruction(instr+ip, 'r', -90);
				ip ++;
			}
			else if(dx==0 && dy==-1){
				setInstruction(instr+ip, 'r', 90);
				ip ++;
			}
			else if(dx==1 && dy==0){
				setInstruction(instr+ip, 'r', 90);
				ip ++;
				setInstruction(instr+ip, 'r', 90);
				ip ++;
			}
			else if(dx==-1 && dy==0){
			}
		}
		ox = dx;
		oy = dy;
		
		setInstruction(instr+ip, 'f', SQUARE);
		ip++;
	}
//	setInstruction(instr+0, 'x', ip);
//	for(i=0; i<ip; i++){
//		TermPrintf("inst: %c %f\n", instr[i].inst, instr[i].value);
//	}
	return instr;
}

void testNode(){
	Node *to_add = malloc(sizeof(Node));
	initNode(to_add, 0, 0, NULL, NULL);
	TermPrintf("testNode: %i, %i\n", to_add->x, to_add->y);
	ButtonWaitForPress(BUTTON_ID_ENTER);
}

void printVisited(){
	int i,j;
	for (i = WIDTH-1; i >= 0; i--) {
		for(j = 0; j < HEIGHT; j++) {
			TermPrintf("%i",visited[i][j]);
		}
		TermPrintf("\n");
	}
	ButtonWaitForPress(BUTTON_ID_ENTER);
}
