// スタックを用いた（再帰を用いない）有向グラフの深さ優先探索 DFS-Stack.c
#include <stdio.h>
#define vmaxsize         1000
#define emaxsize         2000
#include"DigraphInput.h"
// int tail[emaxsize+1], head[emaxsize+1];
// int m, n;
#include"DiStandStructLibrary.h"
// int edgefirst[vmaxsize+1], edgenext[emaxsize+1];
#define unvisited          -1
int parent[vmaxsize+1], prelabel[vmaxsize+1], postlabel[vmaxsize+1];
int current[vmaxsize+1], stack[vmaxsize+1];
int k, j;  // kは先行順のラベル，jは後行順のラベル
int top;   // スタックの先頭を指す
void push(int v){// vからの深さ優先探索の開始
    k++;
    prelabel[v] = k; // vに先行順のラベルkを付ける
    top++;
    stack[top] = v;  // vをスタックに挿入する
}
void pop(void){// スタックの先頭の点の削除
    int v;
    v=stack[top];      // スタックの先頭の点vの削除
    top--;
    j++;               // vからの深さ優先探索の終了
    postlabel[v] = j;  // vに後行順のラベルjを付ける
}
void push_first(int v){
    int a, w;
    k++;
    prelabel[v] = k;  // vに先行順のラベルkを付ける
    top=1;            // 空のスタックの先頭にvを挿入
    stack[top] = v;
    while (top != 0){// スタックが空でない限り
       v=stack[top];   // スタックの先頭の点をvとする
       a = current[v]; // vを始点とする辺のリストで未探索の最初の辺をaとする
       if (a != 0) {// aが実際の辺であるとき（NULLでないとき）
          current[v]=edgenext[a]; // current[v]はaの次の辺を指すように更新
          w = head[a];            // aの終点をwとする
          if (prelabel[w] == unvisited) {// wにラベルがまだ付けられていないとき
             parent[w]=v; // wの親をvとする
             push(w);     // wをスタックに挿入し，wからの深さ優先探索の開始
          }
       }
       else { // aが実際の辺でないとき（a=NULLのとき）
          pop(); // スタックの先頭から点を削除
       }
    }
}
void depth_first_stack(void){
    int v;
    k = 0;  // 先行順ラベル用
    j = 0;  // 後行順ラベル用
    for (v = 1; v <= n; v++) prelabel[v] = unvisited;
       // どの点もラベルが付けられていない
    for (v = 1; v <= n; v++) current[v] = edgefirst[v];
       // current[v]は点vを始点とする辺のリストで未探索の最初の辺を指す
    for (v = 1; v <= n; v++) 
        if (prelabel[v] == unvisited) {
            // 点vにラベルが付けられていないときはvからの深さ優先探索を開始する
            parent[v]=0;   // 新しい深さ優先探索木の根をvとする
            push_first(v); // vからの深さ優先探索の開始
        }    
    printf("\n");
    printf("    点:      先行順      親          後行順\n");
    for (v = 1; v <= n; v++) {
        printf("%6d: %9d %9d %13d\n", v, prelabel[v], parent[v], postlabel[v]);
    }
}
int main(void){
    directed_graph_input(); // 有向グラフの辺数m，点数n，始点，終点が決定される
    distand_incidence_list_construct(); // 接続辺リストが構成される
//  distand_incidence_list_output();    // 構成された接続辺リストが出力される
    depth_first_stack(); // 深さ優先探索の開始
    return 0;
}
