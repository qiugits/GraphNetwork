// 無向グラフ入力と標準的データ構造構成のプログラムstandstruct.c
#include <stdio.h>
#define vmaxsize         1000
#define emaxsize         2000
#define e2maxsize        4000
#include"GraphInput.h"
#include"StandardStructLibrary.h"
int main(void){
    graph_input(); // 無向グラフの辺数m，点数n，始点，終点が決定される
    incidence_list_construct(); // 接続辺リストが構成される
    incidence_list_output();    // 構成された接続辺リストが出力される
    return 0;
}
