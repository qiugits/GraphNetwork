// Hopcroft-Karpの最大マッチングを求めるプログラム hopkarp.c
#include <stdio.h>
#define vmaxsize         1000
#define emaxsize         4000
#define unvisited          -1
#define root                0
#define free                0
#define false               0
#define true                1
#include"BigraphInConstruct.h" // ライブラリBigraphInConstruct.hの読み込み
// int tail[emaxsize+1], head[emaxsize+1];
// int edgefirst[vmaxsize+1], edgenext[emaxsize+1];
// int match[vmaxsize+1];  // 点vをマッチする辺match[v]
// int m, n, n1, n2;       // 左側の点数n1，右側の点数n2，n=n1+n2
#include"LevelConstruct.h"     // ライブラリプログラムLevelConstruct.hの読み込み
// int level[vmaxsize+1];  // レベルグラフにおける点vのレベルlevel[v]
// int queue[vmaxsize+1];  // 幅優先探索のためのキュー
// int max_level;          // マッチされていない右側の点の最小レベル
// int t_found;            // マッチされていない右側の点へ到達したときt_found=true
// int front, rear;        // キューの先頭frontと末尾rear
#include"Augmentation.h"       // ライブラリプログラムAugmentation.hの読み込み
// int parent[vmaxsize+1]; // 深さ優先探索木における点vの親parent[v]
// int pathfound, pathend; // 増加パス（存在 (pathfound=true)，pathendは右側の点）
int main(void){
    int v;
    bipartite_graph_input(); 
    // 二部グラフの辺数m，左側点数n1，右側点数n2，各辺の始点，終点が決定される
    bipartite_incidence_list_construct(); // 接続辺リストが構成される
    bipartite_incidence_list_output(); // 構成された接続辺リストが出力される
    for (v = 1; v <= n; v++) match[v] = free; // 左側のマッチされていない端点から
    do {// マッチされていない左端点からマッチされていない右端点へのパスがある限り
        levelgraph();                        // レベルグラフの構成
        if  (t_found != n+2) augmentation(); // パスがあるときにはマッチングの更新
//     } while (t_found == n+2); これを次の文で置き換える 2017-05-10
    } while (t_found != n+2); 
    matching_output(); // 得られたマッチングの出力
    return 0;
}
