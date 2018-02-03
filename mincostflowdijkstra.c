// Dijkstra法に基づく最小費用フローアルゴリズムのプログラムmincostflowdijkstra.c
#include <stdio.h>
#define vmaxsize         1000
#define emaxsize         2000
#define e2maxsize        4000
#define unvisited          -1
#define true                1
#define false               0
// int head[e2maxsize+1], rescap[e2maxsize+1], cost[e2maxsize+1];
// int edgefirst[vmaxsize+1], edgenext[e2maxsize+1];
// int m, n, s, t;  // これらがMinCostFlowInputLibrary.hで宣言される
#include"MinCostFlowInputLibrary.h" 
#include"DijkstraHeapLibrary.h"
int t_found; // 増加パスが発見されるとtrueになる
// int distance[vmaxsize+1]; 
// int path[vmaxsize+1];
// これらがMinCostDijkstraLibrary.hで宣言される
#include"MinCostDijkstraLibrary.h"
int counter; // 発見された増加パスの個数
#include"MinCostFlowAugmentLibrary.h"
#include"MinCostFlowOutputLibrary.h"
int main(void){
   int v;
   t_found = true; // 増加パスがある可能性があるのでtrueに設定
   flow_network_input(); // ネットワークの
   // 辺数m，点数n，入口s，出口t，各辺の始点，終点，容量，費用が決定される
   flow_incidence_list_construct(); // 各点を始点とする接続辺リストが構成される
   flow_incidence_list_output(); // 各点を始点とする接続辺リストを出力する
   for (v = 1; v <= n; v++) distance[v] = 0;
   counter=0; // 発見された増加パスの個数は0個に初期設定
   t_found = true;
   while (t_found) {
      auxiliary_network_output(); // 補助ネットワークの構成
      t_found=shortest_path_tree_construct(s); 
      // 入口sからすべての点への最短パス木を求め出口tが発見されたらtrueになる
      if (t_found) augmentation(); 
         // trueならばsからtへのパスPに沿ってフローを流す
   }
   mincost_flow_output();
   return 0;
}
