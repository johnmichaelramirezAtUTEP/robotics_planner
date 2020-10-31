#include <stdio.h>
#include <math.h>
#include "parameters.h"
#include <stdlib.h>


#define WIDTH 16
#define HEIGHT 10
#define MWIDTH 4.88
#define MHEIGHT 3.05
#define SQUARE .305

//J:0-15:width
//I:0-9:height

int Board[HEIGHT][WIDTH];
int Gx, Gy;

void printBoard () {
	int i, j;
	printf(" 01234567890123456\n");
	for (i = HEIGHT-1; i >= 0; i--) {
		printf("%d",i);
		for(j = 0; j < WIDTH; j++) {
			printf("%c",Board[i][j]);
		}
		printf("%c",'\n');
	}
}

void initBoard() {
	int i, j;
	for (i = 0; i < HEIGHT; i++) {
		for(j = 0; j < WIDTH; j++) {
			Board[i][j] =  '-';
		}
	}
}

void TranslateCoordinates(double x, double y) {
  if (x != -1 && y != -1) {
    int height = (int) ((y / SQUARE) + .5);
    int width = (int) ((x / SQUARE) + .5);
    //printf("x: %f, y: %f, width: %d, height: %d\n",x,y,width,height);
    Board[height][width] = 'B';
  }
  
  int startx = ((start[0] / SQUARE) + .5);
  int starty = ((start[1] / SQUARE) + .5);
  
  int goalx = ((goal[0] / SQUARE) + .5);
  int goaly = ((goal[1] / SQUARE) + .5);
  
  Board[starty][startx] = 'S';
  Board[goaly][goalx] = 'G';
  Gx = goalx;
  Gy = goaly;
}

void ReadCooordinates() {
  int i, j;
  
  for (i = 0; i < MAX_OBSTACLES; i++)
      TranslateCoordinates(obstacle[i][0],obstacle[i][1]);
    
}

int visited[10][16];

double distance(int x1, int x2, int y1, int y2){
  //return pow(x1-x2, 2) - pow(y1-y2, 2);
  return abs(x1-x2)+abs(y1-y2);
}

typedef struct direction{
  double dist;
  int x,y;
} direction;

void sort(direction dists[4]){
  int min_ind;
  for(int i=0; i<4; i++){
    min_ind = i;
    for(int j=i+1; j<4; j++)
      if(dists[j].dist < dists[min_ind].dist)
        min_ind=j;
      direction temp = dists[i];
      dists[i] = dists[min_ind];
      dists[min_ind] = temp;
  }
}

int found = 0;

void dfs(int x, int y){
  if(found){
    return;
  }
  //printf("exploring x:%d y:%d\n", x, y);
  //printBoard();
  if(Board[y][x] == 'G'){
    //printf("found x:%d y:%d\n", x, y);
    found = 1;
    return;
  }
  if(visited[y][x] == 1){
    return;
  }else{
    visited[y][x] = 1;
    Board[y][x] = '*';
  }

  double dl = distance(Gx,x-1, Gy, y);
  double dr = distance(Gx,x+1, Gy, y);
  double du = distance(Gx,x, Gy, y+1);
  double dd = distance(Gx,x, Gy, y-1);
  
  direction dists[4] = {{dl, x-1, y},{dr, x+1, y},{du, x, y+1},{dd, x, y-1}};
  sort(dists);
  //printf("\n\n\ndists:%f %f %f %f\n", dists[0].dist, dists[1].dist, dists[2].dist, dists[3].dist);

  for(int i=0 ; i<4; i++){
      int xx = dists[i].x;
      int yy = dists[i].y;
    if(xx>=0 && xx<16 && yy>=0 && yy<=10 && Board[xx][yy]!='B')
      dfs(dists[i].x, dists[i].y);
  }

  if(found){
    printf("%d %d\n", x,y);
  }
}

int main () {

  
	initBoard();
  ReadCooordinates();
	printBoard();
  int startx = ((start[0] / SQUARE) + .5);
  int starty = ((start[1] / SQUARE) + .5);
	dfs(startx, starty);
	printBoard();
return 0;	
}
