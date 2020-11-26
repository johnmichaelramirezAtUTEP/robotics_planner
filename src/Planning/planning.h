#ifndef PLANNING_H_
#define PLANNING_H_

struct direction {
  double dist;
  int x,y;
};

struct node {
	int x,y;
	struct node *parent, *next;
};

struct instruction {
	char inst;
	double value;
};

typedef struct node Node;
typedef struct direction Direction;
typedef struct instruction Instruction;

void setupVariables();
void printBoard(void);
void addObstacle(double,double);
void addObstacles(void);
void initBoard(void);
double distance(int,int,int,int);
void sort(Direction *);
void dfs(int,int);
void initNode(Node *, int, int, Node *, Node *);
Node * bfs(void);
void setInstruction(Instruction *, char, double);
void printTrace(Node *);
Instruction * createInstructions(void);

//Test functions
void testNode(void);
void printVisited(void);
int printWD(void);

#endif
