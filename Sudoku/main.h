#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <windows.h>

typedef struct boad {
	//9*9 or 3*3
	int** cell;
	//0:該当なし　1:候補　2:確定
	int*** memo;
	//1:初期数字あり　0:解答欄( 0 )
	int** initial_figure;
} boad;
