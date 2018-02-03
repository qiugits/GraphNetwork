// 有向グラフ入力と標準的データ構造構成のプログラムdistandstruct.c
#include <stdio.h>
#define vmaxsize         1000
#define emaxsize         2000
#include"DigraphInput.h"
#include"DiStandStructLibrary.h"
int main(void){
    directed_graph_input(); // 有向グラフの辺数m，点数n，始点，終点が決定される
    distand_incidence_list_construct(); // 各点を始点とする接続辺リストが構成される
    distand_incidence_list_output();    // 構成された接続辺リストが出力される
    return 0;
}
