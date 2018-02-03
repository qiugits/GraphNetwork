// 無向グラフの深さ優先探索 undirecteddfs.c
#include <stdio.h>
#define vmaxsize         1000
#define emaxsize         2000
#define e2maxsize        4000
#include"GraphInput.h"
#include"StandardStructLibrary.h"
#include"DepthLibrary.h"
int main(void){
    graph_input(); // 無向グラフの辺数m，点数n，始点，終点が決定される
    incidence_list_construct(); // 接続辺リストが構成される
//  incidence_list_output();    // 構成された接続辺リストが出力される
    depth_first(); // 深さ優先探索の開始
    depth_first_output(); // 深さ優先探索の結果が出力される
    return 0;
}
