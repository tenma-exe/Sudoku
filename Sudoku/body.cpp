#include "body.h"

void clear_memo(boad* B,int n_cell) {
	for (int i = 0; i < n_cell;i++) {
		for (int j = 0; j < n_cell;j++) {
			for (int k = 0; k < 10; k++) {
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
	int icell_i, icell_j;
	int zyogai;
	for (i = 0; i < n_cell; i++) {
		for (j = 0; j < n_cell; j++) {

			if (B->cell[i][j] != 0) continue;

			icell_i = i;
			icell_j = j;

			for (k = 0; k < n_cell; k++) {
				if (B->cell[icell_i][k] != 0) {
					zyogai = B->cell[icell_i][k];
					B->memo[icell_i][icell_j][zyogai] = 0;
				}
				if (B->cell[k][icell_j] != 0) {
					zyogai = B->cell[k][icell_j];
					B->memo[icell_i][icell_j][zyogai] = 0;
				}
			}
		}
	}
}

void except_cell(boad* B, int n_cell) {
	int icell_i, icell_j,zyogai;
	for (int i = 0; i < n_cell;i++) {
		for (int j = 0; j < n_cell; j++) {
			//printf("%2d", B->cell[i][j]);
			if (B->cell[i][j] != 0) continue;
			icell_i = i;
			icell_j = j;

			for (int n = 0; n < n_cell; n++) {
				for (int m = 0; m < n_cell; m++) {
					if (B->cell[n][m] != 0) {
						//printf("%2d", B->cell[n][m]);
						zyogai = B->cell[n][m];
						//printf("%2d", B->memo[icell_i][icell_j][zyogai]);
						B->memo[icell_i][icell_j][zyogai] = 0;
						//printf("%2d\n", B->memo[icell_i][icell_j][zyogai]);
					}
				}
			}
		}
	}
}

void memo_data_pass(boad* main_B, boad* nine_B) {
	int i = 0, j = 0, m = 0, k = 0, n = 0, l = 0;
	for (i = 0; i < 9; i++, k++) {
		if (k >= 3) k = 0;
		if (i < 3) n = 0;
		else if (i < 6) n = 3;
		else n = 6;
		for (j = 0, m = 0; j < 9; j++, m++) {
			//[n][k][m]
			if (m >= 3) m = 0;
			if (j != 0 && j % 3 == 0) n++;
			if (main_B->cell[i][j] != 0) continue;
			//printf("%d\n", main_B->cell[i][j]);
			//printf("i:%d j:%d n:%d k:%d m:%d\n", i, j, n, k, m);
			for (l = 0; l < 10; l++) {
				//printf("%2d", nine_B[n].memo[k][m][l]);
				//printf("%2d", main_B->memo[k][m][l]);
				if (nine_B[n].memo[k][m][l] == 0) main_B->memo[i][j][l] = 0;
				//printf("%2d\n", main_B->memo[k][m][l]);
			}
			//printf("\n");
		}
	}
}

void clear_cell_memo(int* memo) {
	for (int k = 0; k < 10; k++) {
		memo[k] = 1;
	}
}

void search_number(boad* main_B, boad* nine_B) {
	int i = 0, j = 0, m = 0, k = 0, n = 0, l = 0;
	int ans, count = 0;
	for (i = 0; i < 9; i++, k++) {
		if (k >= 3) k = 0;
		if (i < 3) n = 0;
		else if (i < 6)n = 3;
		else n = 6;
		for (j = 0, m = 0; j < 9; j++, m++) {
			count = 0;
			//[n][k][m]
			if (m >= 3) m = 0;
			if (j != 0 && j % 3 == 0) n++;
			if (main_B->cell[i][j] != 0) continue;
			//printf("j:%d k:%d n:%d m:%d\n", j, k, n, m);
			for (l = 1; l < 10; l++) {
				if (main_B->memo[i][j][l] == 1) {
					ans = l;
					count++;
				}
			}
			if (count == 1) {
				clear_cell_memo(main_B->memo[i][j]);
				main_B->cell[i][j] = ans;
				nine_B[n].cell[k][m] = ans;
				main_B->memo[i][j][ans] = 2;
				nine_B[n].memo[k][m] = main_B->memo[i][j];
			}
		}
	}
}