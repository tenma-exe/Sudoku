#include "body.h"

void clear_memo(boad* B,int n_cell) {
	for (int i = 0; i < n_cell;i++) {
		for (int j = 0; j < n_cell;j++) {
			for (int k = 0; k <= 9; k++) {
				B->memo[i][j][k] = 1;
			}
		}
	}
}

int cheak_ans(boad* B,int n_cell) {
	for (int i = 0; i < n_cell; i++) {
		for (int j = 0; j < n_cell; j++) {
			if (B->cell[i][j] == 0) return 0;
		}
	}
	return 1;
}

void except_line(boad* B,int n_cell) {
	int i, j, k;
	int zyogai;
	for (i = 0; i < n_cell; i++) {
		for (j = 0; j < n_cell; j++) {
			if (B->cell[i][j] != 0) continue;
			for (k = 0; k < n_cell; k++) {
				//横一列
				if (B->cell[i][k] != 0) {
					zyogai = B->cell[i][k];
					B->memo[i][j][zyogai] = 0;
				}
				//縦一行
				if (B->cell[k][j] != 0) {
					zyogai = B->cell[k][j];
					B->memo[i][j][zyogai] = 0;
				}
			}
		}
	}
}

void except_cell(boad* B, int n_cell) {
	int i = 0, j = 0, tate = 0, yoko = 0;
	int zyogai;
	for (i = 0; i < n_cell;i++) {
		for (j = 0; j < n_cell; j++) {
			if (B->cell[i][j] != 0) continue;
			for (tate = 0; tate< n_cell; tate++) {
				for (yoko = 0; yoko < n_cell; yoko++) {
					if (B->cell[tate][yoko] != 0) {
						zyogai = B->cell[tate][yoko];
						B->memo[i][j][zyogai] = 0;
					}
				}
			}
		}
	}
}

void memo_data_pass(boad* main_B, boad* nine_B,int n_cell) {
	int tate = 0, yoko = 0;
	int	nine_B_yoko = 0, nine_B_tate = 0, nine_blocks = 0, zero_to_nine = 0;
	//nine_blocks:0~8 
	for (tate = 0; tate < n_cell; tate++, nine_B_tate++) {
		if (nine_B_tate >= 3) nine_B_tate = 0;
		if (tate < 3) nine_blocks = 0;
		else if (tate < 6) nine_blocks = 3;
		else nine_blocks = 6;
		for (yoko = 0, nine_B_yoko = 0; yoko < n_cell; yoko++, nine_B_yoko++) {
			//[n][k][m]
			if (nine_B_yoko >= 3) nine_B_yoko = 0;
			if (yoko != 0 && yoko % 3 == 0) nine_blocks++;
			if (main_B->cell[tate][yoko] != 0) continue;
			for (zero_to_nine = 0; zero_to_nine < 10; zero_to_nine++) {
				if (nine_B[nine_blocks].memo[nine_B_tate][nine_B_yoko][zero_to_nine] == 0)
					main_B->memo[tate][yoko][zero_to_nine] = 0;
				else if (main_B->memo[tate][yoko][zero_to_nine] == 0)
					nine_B[nine_blocks].memo[nine_B_tate][nine_B_yoko][zero_to_nine] = 0;
			}
		}
	}
}

void clear_cell_memo(int* memo) {
	for (int i = 0; i < 10; i++) {
		memo[i] = 1;
	}
}

void search_number(boad* main_B, boad* nine_B,int n_cell) {
	int tate = 0, yoko = 0;
	int nine_B_yoko = 0, nine_B_tate = 0, nine_blocks = 0, zero_to_nine = 0;
	int ans, figure_count = 0;
	int mini_n_cell = sqrt(n_cell); //3
	for (tate = 0; tate < n_cell; tate++, nine_B_tate++) {
		if (nine_B_tate >= mini_n_cell) nine_B_tate = 0;
		if (tate < 3) nine_blocks = 0;
		else if (tate < 6) nine_blocks = 3;
		else nine_blocks = 6;
		for (yoko = 0, nine_B_yoko = 0; yoko < n_cell; yoko++, nine_B_yoko++, figure_count = 0) {
			//[n][k][m]
			if (nine_B_yoko >= mini_n_cell) nine_B_yoko = 0;
			if (yoko != 0 && yoko % mini_n_cell == 0) nine_blocks++;
			if (main_B->cell[tate][yoko] != 0) continue;

			for (zero_to_nine = 1; zero_to_nine <= n_cell; zero_to_nine++) {
				if (main_B->memo[tate][yoko][zero_to_nine] == 1) {
					ans = zero_to_nine;
					figure_count++;
				}
			}
			if (figure_count == 1) {
				clear_cell_memo(main_B->memo[tate][yoko]);
				main_B->cell[tate][yoko] = ans;
				nine_B[nine_blocks].cell[nine_B_tate][nine_B_yoko] = ans;
				main_B->memo[tate][yoko][ans] = 2;
				nine_B[nine_blocks].memo[nine_B_tate][nine_B_yoko] = main_B->memo[tate][yoko];
			}
		}
	}
}

void uniNum_in_cells(boad* nine_B,int n_cell) {
	int i = 0, j = 0;
	int one_to_nine = 1;//1～9
	int figure_count = 0, i_ans = 0, j_ans = 0;
	for (one_to_nine = 1, i_ans = 0, j_ans = 0; one_to_nine < 10; one_to_nine++) {
		figure_count = 0;
		for (i = 0; i < n_cell; i++) {
			for (j = 0; j < n_cell; j++) {
				if (nine_B->cell[i][j] == 0 && nine_B->memo[i][j][one_to_nine] == 1) {
					figure_count++;
					i_ans = i;
					j_ans = j;
				}
			}
		}
		if (figure_count == 1) {
			clear_cell_memo(nine_B->memo[i_ans][j_ans]);
			nine_B->cell[i_ans][j_ans] = one_to_nine;
			nine_B->memo[i_ans][j_ans][one_to_nine] = 2;
		}
	}
}

void ansNum_data_pass(boad* main_B, boad* nine_B, int n_cell) {
	int tate = 0, yoko = 0;
	int	nine_B_yoko = 0, nine_B_tate = 0, nine_blocks = 0, zero_to_nine = 0;
	//nine_blocks:0~8 
	for (tate = 0; tate < n_cell; tate++, nine_B_tate++) {
		if (nine_B_tate >= 3) nine_B_tate = 0;
		if (tate < 3) nine_blocks = 0;
		else if (tate < 6) nine_blocks = 3;
		else nine_blocks = 6;
		for (yoko = 0, nine_B_yoko = 0; yoko < n_cell; yoko++, nine_B_yoko++) {
			//[n][k][m]
			if (nine_B_yoko >= 3) nine_B_yoko = 0;
			if (yoko != 0 && yoko % 3 == 0) nine_blocks++;
			if (main_B->cell[tate][yoko] == 0 && nine_B[nine_blocks].cell[nine_B_tate][nine_B_yoko] != 0) {
				main_B->cell[tate][yoko] = nine_B[nine_blocks].cell[nine_B_tate][nine_B_yoko];
				main_B->memo[tate][yoko] = nine_B[nine_blocks].memo[nine_B_tate][nine_B_yoko];
			}
		}
	}
}

void one_Line_judge_yoko(boad* main_B, int n_cell, int n_brock, int jo_chu_ge[3][3], int one_to_nine, int judge_cell ) {
	int i = 0;
	int ignore_area = 3 * judge_cell;
	if (jo_chu_ge[0][judge_cell] == 1 && jo_chu_ge[1][judge_cell] == 0 && jo_chu_ge[2][judge_cell] == 0) {
		for (i = 0; i < n_cell; i++) {
			if ((i >= ignore_area && i < ignore_area + 3) || main_B->cell[n_brock][i] != 0) continue;
			main_B->memo[n_brock][i][one_to_nine] = 0;
		}
	}
	else if (jo_chu_ge[0][judge_cell] == 0 && jo_chu_ge[1][judge_cell] == 1 && jo_chu_ge[2][judge_cell] == 0) {
		for (i = 0; i < n_cell; i++) {
			if ((i >= ignore_area && i < ignore_area + 3) || main_B->cell[n_brock][i] != 0) continue;
			main_B->memo[n_brock + 1][i][one_to_nine] = 0;
		}
	}
	else if (jo_chu_ge[0][judge_cell] == 0 && jo_chu_ge[1][judge_cell] == 0 && jo_chu_ge[2][judge_cell] == 1) {
		for (i = 0; i < n_cell; i++) {
			if ((i >= ignore_area && i < ignore_area + 3) || main_B->cell[n_brock][i] != 0) continue;
			main_B->memo[n_brock + 2][i][one_to_nine] = 0;
		}
	}
}

void dual_Line_judge_yoko(boad* main_B, int n_cell, int n_brock, int jo_chu_ge[3][3], int one_to_nine, int judge_line) {
	int i = 0, j = 0;
	int mini_n_cell = sqrt(n_cell);
	int applicable_area = 0;
	if (jo_chu_ge[judge_line][0] == 1 && jo_chu_ge[judge_line][1] == 0 && jo_chu_ge[judge_line][2] == 0) {
		applicable_area = 0;
		for (j = 0; j < mini_n_cell; j++) {
			for (i = 0; i < n_cell; i++) {
				if (j == judge_line || (i < applicable_area || i >= applicable_area + 3) 
					|| main_B->cell[n_brock + j][i] != 0) continue;
				main_B->memo[n_brock + j][i][one_to_nine] = 0;
			}
		}
	}
	else if (jo_chu_ge[judge_line][0] == 0 && jo_chu_ge[judge_line][1] == 1 && jo_chu_ge[judge_line][2] == 0) {
		applicable_area = 3;
		for (j = 0; j < mini_n_cell; j++) {
			for (i = 0; i < n_cell; i++) {
				if (j == judge_line ||(i < applicable_area || i >= applicable_area + 3)
					|| main_B->cell[n_brock + j][i] != 0) continue;
				main_B->memo[n_brock + j][i][one_to_nine] = 0;
			}
		}
	}
	else if (jo_chu_ge[judge_line][0] == 0 && jo_chu_ge[judge_line][1] == 0 && jo_chu_ge[judge_line][2] == 1) {
		applicable_area = 6;
		for (j = 0; j < mini_n_cell; j++) {
			for (i = 0; i < n_cell; i++) {
				if (j == judge_line || (i < applicable_area || i >= applicable_area + 3)
					|| main_B->cell[n_brock + j][i] != 0) continue;
				main_B->memo[n_brock + j][i][one_to_nine] = 0;
			}
		}
	}
}

void uniLine_jo_chu_ge(boad* main_B, int n_cell, int mini_n_cell, int n_brock) {
	int tate = 0, yoko = 0, cell = 0;
	int one_to_nine = 1;

	//各セルのマーキング　上:[0][0]~[0][2] 中:[1][0]~[1][2] 下:[2][0]~[2][2]
	//1:候補
	int jo_chu_ge[3][3]{0};

	for (one_to_nine = 1; one_to_nine <= n_cell; one_to_nine++) {
		
		//マーキング
		for (tate = n_brock; tate < n_brock + mini_n_cell; tate++) {
			for (yoko = 0, cell = 0; yoko < n_cell; yoko++) {
				if (yoko != 0 && yoko % 3 == 0) cell++;
				if (main_B->cell[tate][yoko] == 0 && main_B->memo[tate][yoko][one_to_nine] == 1) {
					jo_chu_ge[tate - n_brock][cell] = 1;
				}
			}
		}
		
		//判定
		for (int judge_cell = 0; judge_cell < mini_n_cell; judge_cell++) {
			one_Line_judge_yoko(main_B, n_cell, n_brock, jo_chu_ge, one_to_nine, judge_cell);
			dual_Line_judge_yoko(main_B, n_cell, n_brock, jo_chu_ge, one_to_nine, judge_cell);
		}

		//jo_chu_ge[]値リセット
		for (int i = 0; i < mini_n_cell; i++) {
			for (int j = 0; j < mini_n_cell; j++) {
				jo_chu_ge[i][j] = 0;
			}
		}
	}	
}

void one_Line_judge_tate(boad* main_B, int n_cell, int n_brock, int sa_chu_u[3][3], int one_to_nine, int judge_cell) {
	int i = 0;
	int ignore_area = 3 * judge_cell;
	if (sa_chu_u[0][judge_cell] == 1 && sa_chu_u[1][judge_cell] == 0 && sa_chu_u[2][judge_cell] == 0) {
		for (i = 0; i < n_cell; i++) {
			if ((i >= ignore_area && i < ignore_area + 3) || main_B->cell[i][n_brock] != 0) continue;
			main_B->memo[i][n_brock][one_to_nine] = 0;
		}
	}
	else if (sa_chu_u[0][judge_cell] == 0 && sa_chu_u[1][judge_cell] == 1 && sa_chu_u[2][judge_cell] == 0) {
		for (i = 0; i < n_cell; i++) {
			if ((i >= ignore_area && i < ignore_area + 3) || main_B->cell[i][n_brock] != 0) continue;
			main_B->memo[i][n_brock + 1][one_to_nine] = 0;
		}
	}
	else if (sa_chu_u[0][judge_cell] == 0 && sa_chu_u[1][judge_cell] == 0 && sa_chu_u[2][judge_cell] == 1) {
		for (i = 0; i < n_cell; i++) {
			if ((i >= ignore_area && i < ignore_area + 3) || main_B->cell[i][n_brock] != 0) continue;
			main_B->memo[i][n_brock + 2][one_to_nine] = 0;
		}
	}
}

void dual_Line_judge_tate(boad* main_B, int n_cell, int n_brock, int jo_chu_ge[3][3], int one_to_nine, int judge_line) {
	int i = 0, j = 0;
	int mini_n_cell = sqrt(n_cell);
	int applicable_area = 0;
	if (jo_chu_ge[judge_line][0] == 1 && jo_chu_ge[judge_line][1] == 0 && jo_chu_ge[judge_line][2] == 0) {
		applicable_area = 0;
		for (j = 0; j < mini_n_cell; j++) {
			for (i = 0; i < n_cell; i++) {
				if (j == judge_line || (i < applicable_area || i >= applicable_area + 3)
					|| main_B->cell[i][n_brock + j] != 0) continue;
				main_B->memo[i][n_brock + j][one_to_nine] = 0;
			}
		}
	}
	else if (jo_chu_ge[judge_line][0] == 0 && jo_chu_ge[judge_line][1] == 1 && jo_chu_ge[judge_line][2] == 0) {
		applicable_area = 3;
		for (j = 0; j < mini_n_cell; j++) {
			for (i = 0; i < n_cell; i++) {
				if (j == judge_line || (i < applicable_area || i >= applicable_area + 3)
					|| main_B->cell[i][n_brock + j] != 0) continue;
				main_B->memo[i][n_brock + j][one_to_nine] = 0;
			}
		}
	}
	else if (jo_chu_ge[judge_line][0] == 0 && jo_chu_ge[judge_line][1] == 0 && jo_chu_ge[judge_line][2] == 1) {
		applicable_area = 6;
		for (j = 0; j < mini_n_cell; j++) {
			for (i = 0; i < n_cell; i++) {
				if (j == judge_line || (i < applicable_area || i >= applicable_area + 3)
					|| main_B->cell[n_brock + j] != 0) continue;
				main_B->memo[i][n_brock + j][one_to_nine] = 0;
			}
		}
	}
}


void uniLine_sa_chu_u(boad* main_B, int n_cell, int mini_n_cell, int n_brock) {
	int tate = 0, yoko = 0, cell = 0;
	int one_to_nine = 1;

	//各セルのマーキング　左:[0][0]~[0][2] 中:[1][0]~[1][2] 右:[2][0]~[2][2]
	//1:候補
	int sa_chu_u[3][3]{ 0 };

	for (one_to_nine = 1; one_to_nine <= n_cell; one_to_nine++) {

		//マーキング
		for (yoko = n_brock; yoko < n_brock + mini_n_cell; yoko++) {
			for (tate = 0, cell = 0; tate < n_cell; tate++) {
				if (tate != 0 && tate % 3 == 0) cell++;
				if (main_B->cell[tate][yoko] == 0 && main_B->memo[tate][yoko][one_to_nine] == 1) {
					sa_chu_u[yoko - n_brock][cell] = 1;
				}
			}
		}

		//判定
		for (int judge_cell = 0; judge_cell < mini_n_cell; judge_cell++) {
			one_Line_judge_tate(main_B, n_cell, n_brock, sa_chu_u, one_to_nine, judge_cell);
			dual_Line_judge_tate(main_B, n_cell, n_brock, sa_chu_u, one_to_nine, judge_cell);
		}
		
		//sa_chu_u[]値リセット
		for (int i = 0; i < mini_n_cell; i++) {
			for (int j = 0; j < mini_n_cell; j++) {
				sa_chu_u[i][j] = 0;
			}
		}
	}
}