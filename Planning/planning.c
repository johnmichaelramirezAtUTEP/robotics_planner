#include <stdio.h>
#include "parameters.h"


#define WIDTH 16
#define HEIGHT 10
#define MWIDTH 4.88
#define MHEIGHT 3.05
#define SQUARE .305

int Board[WIDTH][HEIGHT];





void printBoard () {
	int i, j;
	for (i = 0; i < HEIGHT; i++) {
		for(j = 0; j < WIDTH; j++) {
			printf("%c",Board[j][i]);
		}
		printf("%c",'\n');
	}
}

void initBoard() {
	int i, j;
	for (i = 0; i < HEIGHT; i++) {
		for(j = 0; j < WIDTH; j++) {
			Board[j][i] =  '-';
		}
	}
}

void TranslateCoordinates(double x, double y) {
  if (x != -1 && y != -1) {
    int height = (int) ((y / SQUARE) + .5);
    int width = (int) ((x / SQUARE) + .5);
    printf("x: %f, y: %f, width: %d, height: %d\n",x,y,width,height);
    Board[width][height] = 'B';
  }
  
  int startx = ((start[0] / SQUARE) + .5);
  int starty = ((start[1] / SQUARE) + .5);
  
  int goalx = ((goal[0] / SQUARE) + .5);
  int goaly = ((goal[1] / SQUARE) + .5);
  
  Board[startx][starty] = 'S';
  Board[goalx][goaly] = 'G';
}

void ReadCooordinates() {
  int i, j;
  
  for (i = 0; i < MAX_OBSTACLES; i++)
      TranslateCoordinates(obstacle[i][0],obstacle[i][1]);
    
}



int main () {
	initBoard();
  ReadCooordinates();
	printBoard();
return 0;	
}
