#ifndef PLANNING_H_
#define PLANNING_H_

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
void createInstructions(void);

#endif
