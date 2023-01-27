#include "body.h"

void clear_memo(boad* B,int n_cell) {
	for (int i = 0; i < n_cell;i++) {
		for (int j = 0; j < n_cell;j++) {
			for (int k = 0; k <= n_cell; k++) {
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
				//‰¡ˆê—ñ
				if (B->cell[i][k] != 0) {
					zyogai = B->cell[i][k];
					B->memo[i][j][zyogai] = 0;
				}
				//cˆês
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
		for (yoko = 0, nine_B_yoko = 0; yoko < n_cell; yoko++, nine_B_yoko++) {
			figure_count = 0;
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