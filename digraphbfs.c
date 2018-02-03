// 有向グラフの幅優先探索 digraphbfs.c
#include <stdio.h>
#define vmaxsize         1000
#define emaxsize         2000
#include"DigraphInput.h"
#include"DiStandStructLibrary.h"
#include"BreadthLibrary.h"
int main(void){
    directed_graph_input(); // 有向グラフの辺数m，点数n，始点，終点が決定される
    distand_incidence_list_construct(); // 接続辺リストが構成される
//  distand_incidence_list_output();    // 構成された接続辺リストが出力される
    breadth_first();  // 幅優先探索の開始
    breadth_first_output(); // 幅優先探索の結果が出力される
    return 0;
}
