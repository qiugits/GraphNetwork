// Dinicの最大フローアルゴリズムのプログラム dinic.c
#include <stdio.h>
#define vmaxsize          100
#define emaxsize          400
#define e2maxsize         800
#define unvisited          -1
#define true                1
#define false               0
#include"FlowLibrary.h"
int t_found; // 増加パスが発見されるとtrueになる
int counter; // 発見された増加パスの個数
int level_graph(int level[]){
   int queue[vmaxsize+1]; 
   int a, v, w, front, rear, t_found;
   for (v = 1; v <= n; v++) level[v] = unvisited;
   rear = 1; front = 1;
   t_found=false;
   level[s] = 0; queue[rear] = s;
   while (front <= rear) {
      v = queue[front]; // vからの幅優先探索をする
      front++;
      a=edgefirst[v];
      while (a != 0) {
         if (rescap[a]==0) a = edgenext[a];
         else {// aはrescap[a]>0なので残容量ネットワークの辺
            w = head[a];
            a = edgenext[a];
            if (level[w] == unvisited) {
               level[w] = level[v]+1;
               if (w != t){// wをキューの末尾に挿入
                  rear++; queue[rear]=w;
               }
               else {// tに到達したので強制終了する
                  t_found=true; front=rear+1; a=0;
               }
            }
         }
      }
   }
   return(t_found);
}
void dfs_dinic(int v, int current[], int path[], int level[]){
// vからの深さ優先探索
   int afwd, abk, u, w;
   if (current[v] != 0) {
//   if (current[v] == 0) {
//      abk = path[v]; 
//      u = head[abk];
//      if (current[u] != 0) current[u] = edgenext[current[u]]; 
//   }
//   else {// current[v] != 0
      afwd = current[v];
//      while (afwd != 0 && (level[head[afwd]] != level[v]+1 || rescap[afwd] == 0)) 
//         afwd = edgenext[afwd];
//      current[v]=afwd; // ここでたどる辺が決定された
      while (t_found == false && afwd != 0) {// 増加パスはまだ発見されいない
         while (afwd != 0 && (level[head[afwd]] != level[v]+1 || rescap[afwd] == 0)) 
            afwd = edgenext[afwd];
         current[v]=afwd; // ここでたどる辺が決定された
         if (afwd != 0) {
            w = head[afwd]; // wへと辺をたどる
            if (path[w] == unvisited) {// wが未訪問であったらwへ前進
               abk = afwd+1; 
               if (afwd % 2 ==0) abk = afwd-1; // abkはafwdの逆向きの辺
               path[w] = abk; // afwdの逆向きの辺abkをpath[w]に記憶する
               if (w != t) {
                  dfs_dinic(w,current,path,level); // wからの深さ優先探索へ進む
               }
               else {// w == t なので増加パスPが見つかった
                  t_found=true; // dfs_dinic(v,current,path,level)の強制終了へ
               }
            }
//          else { // wからは増加パスでtへは到達できないことがすでにわかっている
//             afwd = edgenext[afwd]; //次の辺に移る
//             current[v]=afwd;
//          }
            if (t_found == false) {// dfs_dinic(v,current,path,level)の強制終了に対応するため
               afwd = edgenext[afwd]; //次の辺に移る
//               while (afwd != 0 && (level[w] != level[v]+1 || rescap[afwd] == 0)) 
//                  afwd = edgenext[afwd]; 
               current[v]=afwd;
            }
         }
      }
   }
}
void augmentation_dinic(int current[], int path[], int level[]){
   // レベルネットワークで増加パスPを求めてPに沿ってフローを流すことを繰り返す
   int afwd, abk, v, w, delta, cap;
   for (v = 1; v <= n; v++) current[v]= edgefirst[v]; // 初期設定
   while (current[s] != 0) {// sを始点とする辺が存在する限り
      for (v = 1; v <= n; v++) path[v] = unvisited; // 初期設定
      path[s]=0; // sは増加パスの出発点と設定
      t_found=false; // 増加パスはまだ発見されいないと設定
      dfs_dinic(s,current,path,level); // レベルネットワークで増加パスPを求める
      if (t_found == true) {// 増加パスPの辺を逆にたどりdelta=Δ(P)を求める
         counter++; // 発見された増加パスの個数を1増やす
         abk=path[t]; //abkはPの最後の辺の逆向きの辺でtは辺abkの始点
         afwd = abk+1; 
         if (abk % 2 == 0) afwd=abk-1; // afwdはPの最後の辺でtはafwdの終点
         delta = rescap[afwd]; // P上の辺の残容量の最小値Δ(P)の計算ための初期化
         v = head[abk]; // vは増加パスPでtの直前の点
         while (v != s) {// sに到達するまでPを逆にたどる
            abk = path[v]; // abkはvは入るPの辺の逆向きの辺
            v = head[abk]; // vを増加パスPでvの直前の点に更新
            afwd = abk+1;
            if (abk % 2 == 0) afwd = abk-1; // afwdはPの辺でabkの逆向きの辺
            if (delta > rescap[afwd]) delta = rescap[afwd];// 残容量を更新
            // deltaは最終的にはdelta=Δ(P)となる
         }
         printf("\n");
         printf("Δ（P%d)= %d\n", counter,delta);
         v = t;
         while (v != s) {// 増加パスに沿ってdelta=Δ(P)だけフローを送り込む
            abk = path[v]; // abkはPの辺の逆向きの辺
            v = head[abk];
            afwd = abk+1; 
            if (abk % 2 == 0) afwd = abk-1; // afwdはPの辺
            cap = rescap[afwd]+rescap[abk];
            rescap[afwd] = rescap[afwd]-delta;
            rescap[abk] = rescap[abk]+delta;
            if (afwd % 2 ==0) {// afwdはNの本来の辺
               printf("辺%2d  始点%2d  終点%2d  容量%2d   f(%2d):%2d --> %2d\n", 
               afwd/2,head[abk],head[afwd],cap,afwd/2,rescap[abk]-delta,
               rescap[abk]);
            }
            else {// afwdはNにはなかった仮想的な辺で本来の辺abkの逆向きの辺
               printf("辺%2d  始点%2d  終点%2d  容量%2d   f(%2d):%2d --> %2d\n", 
               abk/2,head[afwd],head[abk],cap,abk/2,rescap[afwd]+delta,
               rescap[afwd]);
            }
         }
      }
   }
}
int main(void){
int current[vmaxsize+1];
int path[vmaxsize+1];
int level[vmaxsize+1];
   t_found = true; // 増加パスがある可能性があるのでtrueに設定
   flow_network_input(); 
   // ネットワークの辺数m，点数n，入口s，出口t，各辺の始点，終点，容量が決定される
   flow_incidence_list_construct(); // 各点を始点とする接続辺リストが構成される
   counter=0; // 発見された増加パスの個数は0個に初期設定
   while (t_found) {
      t_found = level_graph(level); 
      // t_foundをfalseに設定し増加パスがあるとわかるとtrueになる
      if (t_found) {// 増加パスが存在するとき
         augmentation_dinic(current,path,level); // t_foundをfalseに設定し
         // レベルネットワークで増加パスPを求めてPに沿ってフローを流すことを反復
         t_found = true;
      }    
   }
   max_flow_output();
   min_cut_output(level);
   return 0;
}
