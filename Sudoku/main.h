#pragma once
#include <stdlib.h>
#include <math.h>
#include <iostream>


typedef struct boad {
	//9*9 or 3*3
	int** cell;
	//0:ŠY“–‚È‚µ@1:Œó•â@2:Šm’è
	int*** memo;
} boad;
