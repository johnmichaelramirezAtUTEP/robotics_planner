#include <stdio.h>
#include <math.h>
#include "parameters.h"
#include <stdlib.h>


#define WIDTH 16
#define HEIGHT 10
#define MWIDTH 4.88
#define MHEIGHT 3.05
#define SQUARE .305

int Board[HEIGHT][WIDTH];
int Gx, Gy;
int Sx, Sy;

void printBoard () {
	int i, j;
	for (i = HEIGHT-1; i >= 0; i--) {
		printf("%d",i);
		for(j = 0; j < WIDTH; j++) {
			printf("%c",Board[i][j]);
		}
		printf("%c",'\n');
	}
	printf(" 01234567890123456\n");
}

void add_obstacle(double x, double y) {
  if (x != -1 && y != -1) {
    int height = (int) ((y / SQUARE) + .5);
    int width = (int) ((x / SQUARE) + .5);
    //printf("x: %f, y: %f, width: %d, height: %d\n",x,y,width,height);
    Board[height][width] = 'B';
  }
}

void add_obstacles() {
  for (int i = 0; i < MAX_OBSTACLES; i++)
      add_obstacle(obstacle[i][0],obstacle[i][1]);
}

void initBoard() {
	for (int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			Board[i][j] =  '-';
		}
	}

  Sx = ((start[0] / SQUARE) + .5);
  Sy = ((start[1] / SQUARE) + .5);

  Gx = ((goal[0] / SQUARE) + .5);
  Gy = ((goal[1] / SQUARE) + .5);

  Board[Sy][Sx] = 'S';
  Board[Gy][Gx] = 'G';

  add_obstacles();
}

int visited[HEIGHT][WIDTH] = {0};

double distance(int x1, int x2, int y1, int y2){
  return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
  //return abs(x1-x2)+abs(y1-y2);
}

//dfs code
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
  if(Board[y][x] == 'G'){
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

  for(int i=0 ; i<4; i++){
      int xx = dists[i].x;
      int yy = dists[i].y;
    if(xx>=0 && xx<16 && yy>=0 && yy<10 && Board[yy][xx]!='B')
      dfs(dists[i].x, dists[i].y);
  }

  if(found){
    printf("%d %d\n", x,y);
  }
}

// bfs code
typedef struct node{
	int x,y;
	struct node *parent, *next;
} node;

void init_node(node *self, int x, int y, node *parent, node *next){
	self->x = x;
	self->y = y;
	self->parent = parent;
	self->next = next;
}

node * bfs(){
	//queue
	node *head = malloc(sizeof(node));
	init_node(head, Sx, Sy, NULL, NULL);
	node *tail = head;
	//add start to queue
	//while queue not empty
	while(head != NULL){
		node *current = head;
		//printf("current: %p, x:%d, y:%d\n", current, current->x, current->y);

		//if at goal, backtrace
		if(current->x == Gx && current->y == Gy){
			printf("found goal\n");
			return current;
		}

		//add all legal locations to end of queue
		int x = current->x, y = current->y;
		int directions [4][2] = {{x-1, y},{x+1, y},{x, y+1},{x, y-1}};
		for(int i=0; i<4; i++){
			int xx = directions[i][0];
			int yy = directions[i][1];
			if(xx>=0 && xx<16 && yy>=0 && yy<10 && Board[yy][xx]!='B' && !visited[xx][yy]){
				if(xx==6 && yy==4){
					printf("adding blocked %c\n", Board[yy][xx]);
				}
				visited[xx][yy] = 1;
				node *to_add = malloc(sizeof(node));
				init_node(to_add, xx, yy, current, NULL);
				tail->next = to_add;
				tail = tail->next;
			}
		}

		//increment queue pointer
		head = head->next;
	}
	return NULL;
}

void print_trace(node *goal){
	while(goal != NULL){
		printf("%d, %d\n", goal->x, goal->y);
		Board[goal->y][goal->x] = '*';
		goal = goal->parent;
	}
}

int main () {
  initBoard();
  add_obstacles();
	printBoard();
	//dfs(Sx, Sy);
	node *backtrace = bfs();
	print_trace(backtrace);
	printBoard();
	return 0;	
}
