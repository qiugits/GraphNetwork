// 無向グラフ入力と標準的データ構造構成と配列出力のプログラムstandstructarray.c
#include <stdio.h>
#define vmaxsize         1000
#define emaxsize         2000
#define e2maxsize        4000
#include"GraphInput.h"
#include"StandardStructEx.h"
int main(void){
    graph_input(); // 無向グラフの辺数m，点数n，始点，終点が決定される
    incidence_list_construct();  // 接続辺リストが構成される
    incidence_list_output();     // 構成された接続辺リストが出力される
    outputarray(); // 追加した行 // 標準的データ構造の配列の内容が出力される
    return 0;
}    
