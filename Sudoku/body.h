#pragma once
#include "main.h"

void clear_memo(boad* B, int n_cell);

int cheak_ans(boad* B,int n_cell);

void except_line(boad* B,int n_cell);

void except_cell(boad* B,int n_cell);

void memo_data_pass(boad* main_B,boad* nine_B,int n_cell);

void clear_cell_memo(int* memo);
void search_number(boad* main_B, boad* nine_B,int n_cell);