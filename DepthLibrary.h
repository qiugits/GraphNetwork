// 深さ優先探索ライブラリプログラム DepthLibrary.h
#include <stdio.h>
#define unvisited -1
#define vmaxsize 1000
#define emaxsize 2000
int parent[vmaxsize+1], prelabel[vmaxsize+1], postlabel[vmaxsize+1];
int edgefirst[vmaxsize+1];
int head[emaxsize+1], tail[emaxsize+1];
int edgenext[emaxsize+1];
int k, j;  // kは先行順のラベル，jは後行順のラベル
int n;
void dfs(int v){// vからの深さ優先探索を行う再帰的な関数
    int a, w;
    k++;
    prelabel[v] = k; // vに先行順のラベルkを付ける
    a = edgefirst[v]; // aはvを始点とする辺のリストの先頭の辺
    while (a != 0) {// aがvを始点とする辺のリストの最後になるまで
        w = head[a];  // aの終点をwとする
        if (prelabel[w] == unvisited) {// wにラベルがまだ付けられていないとき
            dfs(w);  // wからの深さ優先探索の再帰呼び出し
            parent[w] = v; // wの親をvとする
        }
        a = edgenext[a]; // vを始点とする辺のリストでaの次の辺をaをする
    } // vからの深さ優先探索の終了
    j++;
    postlabel[v] = j; // vに後行順のラベルjを付ける
}
void depth_first(void){// 深さ優先探索を行う関数
    int v;
    k = 0;  // 先行順ラベル用
    j = 0;  // 後行順ラベル用
    for (v = 1; v <= n; v++) prelabel[v] = unvisited; 
       // どの点もラベルが付けられていない
    for (v = 1; v <= n; v++) 
        if (prelabel[v] == unvisited){
            // 点vにラベルが付けられていないときはvからの深さ優先探索を開始する
            parent[v]=0; // 新しい深さ優先探索木の根をvとする
            dfs(v);  // vからの深さ優先探索の開始
        }    
}
void depth_first_output(void){// 深さ優先探索の結果を出力する関数
    int v;
    printf("\n");
    printf("    点:      先行順      親          後行順\n");
    for (v = 1; v <= n; v++) {
        printf("%6d: %9d %9d %13d\n", v, prelabel[v], parent[v], postlabel[v]);
    }
}
