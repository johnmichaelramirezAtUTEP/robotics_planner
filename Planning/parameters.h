#ifndef PARMS
#define PARMS

#define S .305
#define MAX_OBSTACLES 25 /* maximum number of obstacles */

//int num_obstacles = 13; /* number of obstacles */
//double obstacle[MAX_OBSTACLES][2] = /* obstacle locations */
//{{0.61, 2.743},{0.915, 2.743},{1.219, 2.743},{1.829, 1.219},
//{1.829, 1.524},{ 1.829, 1.829}, {1.829, 2.134},{2.743, 0.305},
//{2.743, 0.61},{2.743, 0.915},{2.743, 2.743},{3.048, 2.743},
//{3.353, 2.743},
//{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
//{-1,-1},{-1,-1},{-1,-1}};
//
//double start[2] = {0.305, 1.219}; /* start location */
//double goal[2] = {3.658, 1.829}; /* goal location */

int num_obstacles = 17; /* number of obstacles */
double obstacle[MAX_OBSTACLES][2] = /* obstacle locations */
{{7*S, 7*S},{8*S, 7*S},{9*S, 7*S},{10*S, 7*S}, {11*S, 7*S},
{7*S, 3*S},{8*S, 3*S},{9*S, 3*S},{10*S, 3*S}, {11*S, 3*S},
{9*S, 5*S}, 
{12*S, 6*S}, {12*S, 5*S}, {12*S, 4*S},
{14*S, 6*S}, {14*S, 4*S}, {15*S, 5*S}};

double start[2] = {14*S, 5*S}; /* start location */
double goal[2] = {10*S, 5*S}; /* goal location */

#endif

//9----------------
//8----------------
//7-------BBBBB----
//6------------B-B-
//5---------BG-B-SB
//4------------B-B-
//3-------BBBBB----
//2----------------
//1----------------
//0----------------
// 01234567890123456
