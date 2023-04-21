#pragma once
#include "main.h"

void clear_memo(boad* B, int n_cell);

int cheak_ans(boad* B,int n_cell);

void except_line(boad* B,int n_cell);

void except_cell(boad* B,int n_cell);

void memo_data_pass(boad* main_B,boad* nine_B,int n_cell);

void clear_cell_memo(int* memo);

void search_number(boad* main_B, boad* nine_B,int n_cell);

void uniNum_in_cells(boad* nine_B,int n_cell);

void ansNum_data_pass(boad* main_B, boad* nine_B, int n_cell);

void one_Line_judge_yoko(boad* main_B, int n_cell, int n_brock, int jo_chu_ge[3][3], int one_to_nine, int judge_cell);

void uniLine_jo_chu_ge(boad* main_B, int n_cell, int mini_n_cell, int n_brock);

void one_Line_judge_tate(boad* main_B, int n_cell, int n_brock, int jo_chu_ge[3][3], int one_to_nine, int judge_line);

void uniLine_sa_chu_u(boad* main_B, int n_cell, int mini_n_cell, int n_brock);