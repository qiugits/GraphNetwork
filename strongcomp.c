// 強連結成分分解プログラム strongcomp.c
#include <stdio.h>
#define vmaxsize         1000
#define emaxsize         2000
#include"DigraphInput.h"
#include"CompStructLibrary.h"
#include"PostLibrary.h"
#include"StrongCompLibrary.h"
int main(void){
    directed_graph_input(); // 有向グラフの辺数m，点数n，始点，終点が決定される
    dicomp_incidence_list_construct(); // 接続辺リストが構成される
    postsort();  // 点が後行順にソートされる
    stcomp_construct(); // 各点が属する強連結成分が決定され  
       // さらに各強連結成分に含まれる点と辺のリストが構成される
    stcomponent_output(); // 強連結成分が出力される
    return 0;
}
