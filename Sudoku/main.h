#pragma once
#include <stdlib.h>
#include <math.h>
#include <iostream>


typedef struct boad {
	//9*9 or 3*3
	int** cell;
	//0:�Y���Ȃ��@1:���@2:�m��
	int*** memo;
} boad;
