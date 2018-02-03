// 有向グラフ入力と完備データ構造構成と配列出力のプログラムcompstructarray.c
#include <stdio.h>
#define vmaxsize         1000
#define emaxsize         2000
#include"DigraphInput.h"
#include"CompStructEx.h"
int main(void){
    directed_graph_input(); // 有向グラフの辺数m，点数n，始点，終点が決定される
    dicomp_incidence_list_construct(); // 接続辺リストが構成される
    dicomp_incidence_list_output();    // 構成された接続辺リストが出力される
    outputarray(); // 追加した行      // 完備データ構造の配列の内容が出力される
    return 0;
}
