#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <windows.h>

typedef struct boad {
	//9*9 or 3*3
	int** cell;
	//0:�Y���Ȃ��@1:���@2:�m��
	int*** memo;
	//1:������������@0:�𓚗�( 0 )
	int** initial_figure;
} boad;
