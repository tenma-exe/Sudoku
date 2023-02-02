// Sudoku.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "main.h"
#include "body.h"
#include <string.h>
#pragma warning(disable:4996)
#define n_cell 9


boad* Nine_cell;
boad* Main_boad;

void finalize() {
    //int i, j, k;
    /*for (i = 0; i < n_cell; i++) {
        for (j = 0; j < 3; j++) {
            free(Nine_cell[i].cell[j]);
            for (k = 0; k < 3;k++) {
                free(Nine_cell[i].memo[j][k]);
            }
            free(Nine_cell[i].memo[j]);
        }
    }*/
    free(Nine_cell);
    /*for (i = 0; i < n_cell; i++) { 
        free(Main_boad->cell[i]);
        for (j = 0; j < n_cell;j++) {
            free(Main_boad->memo[i][j]);
        }
    }
    free(Main_boad->cell);*/
    free(Main_boad);
}

void read_data(boad* Main_boad) {
    FILE* fp;
    int i,j;
    int icell = 0;
    int mini_n_cell = sqrt(n_cell);//3
    const char* fname = "Sudoku_data.txt";
    if ((fp = fopen(fname, "r")) == NULL) {
        printf("Not open %s\n", fname);
        exit(EXIT_FAILURE);
    }
    else {
        printf("%s file is opened\n",fname);
    }
    for (i = 0; i < n_cell; i++) {
        fscanf_s(fp, "%d %d %d %d %d %d %d %d %d \n"
            , &Main_boad->cell[i][0], &Main_boad->cell[i][1], &Main_boad->cell[i][2]
            , &Main_boad->cell[i][3], &Main_boad->cell[i][4], &Main_boad->cell[i][5]
            , &Main_boad->cell[i][6], &Main_boad->cell[i][7], &Main_boad->cell[i][8]
            );
        for (j = 0; j < n_cell;j++) {
            icell = Main_boad->cell[i][j];
            Main_boad->memo[i][j][icell] = 2;
        }
    }
    Nine_cell = (boad*)malloc(sizeof(boad) * n_cell);
    if (Nine_cell) {
        for (int k = 0; k < n_cell; k++) {
            Nine_cell[k].cell = (int**)malloc(sizeof(int*) * mini_n_cell);
            Nine_cell[k].memo = (int***)malloc(sizeof(int**) * mini_n_cell);
            for (i = 0; i < mini_n_cell; i++) {
                if (Nine_cell[k].cell != NULL && Nine_cell[k].memo != NULL) {
                    Nine_cell[k].cell[i] = (int*)malloc(sizeof(int) * mini_n_cell);
                    Nine_cell[k].memo[i] = (int**)malloc(sizeof(int*) * mini_n_cell);
                    for (j = 0; j < n_cell; j++) {
                        if (Nine_cell[k].memo[i] != NULL) Nine_cell[k].memo[i][j] = (int*)malloc(sizeof(int) * (n_cell + 1));
                    }
                }
            }
            
        }
    }

    for (i = 0; i < n_cell; i++) {
        if(Nine_cell) clear_memo(&Nine_cell[i], mini_n_cell);
    }
    int m = 0, k = 0, n = 0;
    for (i = 0; i < n_cell; i++, k++) {
        if (k >= mini_n_cell) k = 0;
        if (i < 3) n = 0;
        else if (i < 6)n = 3;
        else n = 6;
        for (j = 0, m = 0; j < n_cell; j++, m++) {
            if (m >= mini_n_cell) m = 0;
            if (j != 0 && j % mini_n_cell == 0) n++;
            icell = Main_boad->cell[i][j];
            if (Nine_cell && Nine_cell[n].cell && Nine_cell[n].cell[k]
                && Nine_cell[n].memo && Nine_cell[n].memo[k] && Nine_cell[n].memo[k][m]) {
                Nine_cell[n].cell[k][m] = icell;
                Nine_cell[n].memo[k][m][icell] = Main_boad->memo[i][j][icell];
            }
            
        }
    }
    fclose(fp);
}

void display_boad(boad disp_boad,int n) {
    for (int i = 0; i < n;i++) {
        for (int j = 0; j < n;j++) {
            printf("%2d", disp_boad.cell[i][j]);
        }
        printf("\n");
    }
}

int i_test = 0, j_test = 2, cell_num = 1;

void display_memo(int num,int* memo) {
    printf("cell[%d][%d]:%d\n", i_test, j_test,num);
    for (int i = 0; i <= n_cell; i++) {
        printf("memo[ %d ]: %d\n", i, memo[i]);
    }
}

void cal_Process(){
    int time_limit = 0;
    int mini_n_cell = sqrt(n_cell); //3
    while (1) {
        except_line(Main_boad, n_cell);
        search_number(Main_boad, Nine_cell, n_cell);
        memo_data_pass(Main_boad, Nine_cell, n_cell);
        for (int i = 0; i < n_cell; i++) {
            except_cell(&Nine_cell[i], mini_n_cell);
        }
        memo_data_pass(Main_boad, Nine_cell, n_cell);
        search_number(Main_boad, Nine_cell, n_cell);
        for (int i = 0; i < n_cell;i++) {
            uniNum_in_cells(&Nine_cell[i], mini_n_cell);
        }
        ansNum_data_pass(Main_boad,Nine_cell,n_cell);
        time_limit++;
        if (cheak_ans(Main_boad, n_cell)) {
            printf("Complete : %d counts\n",time_limit);
            break; 
        }
        if (time_limit>=10000) {
            printf("It's time over! : %d counts\n",time_limit);
            break;
        }
    }
}

int main()
{
    Main_boad = (boad*)malloc(sizeof(boad));
    if (Main_boad) {
        Main_boad->cell = (int**)malloc(sizeof(int*) * n_cell);
        Main_boad->memo = (int***)malloc(sizeof(int**) * n_cell);
    }
    for (int i = 0; i < n_cell; i++){
        if (Main_boad&&Main_boad->cell&& Main_boad->memo) {
            Main_boad->cell[i] = (int*)malloc(sizeof(int) * n_cell);
            Main_boad->memo[i] = (int**)malloc(sizeof(int*) * n_cell);
        }
        for (int j = 0; j < n_cell;j++) {
            if (Main_boad && Main_boad->memo && Main_boad->memo[i]) {
                Main_boad->memo[i][j] = (int*)malloc(sizeof(int) * (n_cell + 1));
            }
        }
    }
    clear_memo(Main_boad, n_cell);
    read_data(Main_boad);
    printf("First posion:\n");
    if (Main_boad) display_boad(*Main_boad, n_cell);
    display_memo(Nine_cell[cell_num].cell[i_test][j_test], Nine_cell[cell_num].memo[i_test][j_test]);

    cal_Process();
    printf("result:\n");
    if (Main_boad) display_boad(*Main_boad, n_cell);
    display_memo(Nine_cell[cell_num].cell[i_test][j_test],Nine_cell[cell_num].memo[i_test][j_test]);
    finalize();
    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
