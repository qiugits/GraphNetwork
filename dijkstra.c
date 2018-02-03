// Dijkstraの最短パス木を求めるプログラム dijkstra.c
#include <stdio.h>
#define vmaxsize         1000
#define emaxsize         3000
#define unvisited          -1
#define true                1
#define false               0
#include"DiNetworkInput.h"
// int tail[emaxsize+1], head[emaxsize+1], length[emaxsize+1];
#include"DiStandStructLibrary.h"
// int edgefirst[vmaxsize+1], edgenext[emaxsize+1];
int heap[vmaxsize+1], inv_heap[vmaxsize+1];
int distance[vmaxsize+1]; 
int path[vmaxsize+1];
// int m, n;
int start;
void shift_down(int p, int q) {// 配列の番地pから番地qまでの部分での下移動
    int r,v;
   while (2*p <= q) {
      // ヒープのノードpを根とする部分木がq以下のノードを子としてもつ限り
      r=2*p; // rをpの左の子とする
      if (r+1<=q && distance[heap[r+1]] < distance[heap[r]]) r=r+1;
      // pが右の子ももつときは距離の小さいほうをrをする
      if (distance[heap[p]] > distance[heap[r]]) {
      // pよりもrのほうが小さいときにはpとrに割り当てられている点を交換する 
         inv_heap[heap[r]]=p; 
         inv_heap[heap[p]]=r; 
         v=heap[p]; 
         heap[p]=heap[r]; 
         heap[r]=v; 
         p=r; // pを子のノードrとして下移動する
      }
      else p=q; // 強制終了へ進む
   }
}
void shift_up(int p) {// 配列の番地pからの上移動
   int r,v;
   while (p > 1) {// pが根でない限り
      r=p/2;   // rをpの親とする
      if (distance[heap[p]] < distance[heap[r]]) {
      // rよりもpのほうが小さいときにはpとrに割り当てられている点を交換する 
         inv_heap[heap[r]]=p; 
         inv_heap[heap[p]]=r;
         v=heap[p]; 
         heap[p]=heap[r]; 
         heap[r]=v; 
         p=r; // pを親のノードrとして上移動する
      }
      else p=1; 
   }
}
void shortest_path_tree_construct(void){// startを根とする最短パス木の構成
   int a,v,v1,v2;
   int i;
   for (v = 1; v <= n; v++) path[v] = unvisited;
   distance[start]=0; // 出発点startからstartまでの距離は0と初期設定
   path[start]=0;    // 出発点startは最短パス木の根に初期設定
   heap[1]=start;    // ヒープにstartを挿入
   inv_heap[start]=1; // startのヒープでのノードは1と初期設定
   i=1; 
   while (i > 0) {// ヒープが空になるまで以下を繰り返す
      v1=heap[1]; // VPに含まれない点で距離が最小の点をv1とする
      heap[1]=heap[i]; // ヒープの最後のノードに記憶されている点を根に移す
      inv_heap[heap[1]]=1; 
      // ヒープの根に記憶されている点にヒープでのノードが1（根）であるとする
      i=i-1; // ヒープのサイズを1減らす
      if (i > 1) shift_down(1,i); // 下移動に基づいてヒープが構成される
      a=edgefirst[v1]; // aはv1を始点とする辺のリスト最初の辺
      while (a != 0) {// v1を始点とする辺のリストの最後の辺になるまで
         v2=head[a];
         if (path[v2]==unvisited) {// 辺aの終点がVPにないとき
            distance[v2]=distance[v1]+length[a]; // v2までの暫定的距離の設定
            path[v2]=a; // v2までのこれまでの最短パスの最後の辺はa
            i=i+1;   // ヒープのサイズを1増やしそこにv2を挿入する
            heap[i]=v2;   // ヒープのノードiにv2を記憶する     
            inv_heap[v2]=i; 
               // v2が記憶されているヒープのノードはiとしてv2に記憶    
            shift_up(i);  // iからの上移動に基づくヒープの再構成             
         }                                          
         else if (distance[v2]>distance[v1]+length[a]) {
            // より短いパスが発見された       
            distance[v2]=distance[v1]+length[a]; // こちらのパスに更新する   
            path[v2]=a; // v2までの最短パスの最後の辺をaに更新する         
            shift_up(inv_heap[v2]); 
               // v2が記憶されているヒープのノードから上移動する        
         }                          
         a=edgenext[a];                     
      }                               
   }                              
}
void shortest_path_output(void){
   int a,v;
   printf("\n出発点%2dからのすべての点への最短パス木\n",start);
   for (v = 1; v <= n; v++) {
      if (v != start) {
         a=path[v]; 
         printf("%2dまでの距離は%2dでありパスの最後の辺は長さ%2dの辺%2d=(%d,%d)\n",
                 v,distance[v],length[a],a,tail[a],v);
      }   
   }
}
int main(void){
   directed_network_input(); 
   // 有向ネットワークの辺数m，点数n，各辺の始点，終点，長さが決定される
   distand_incidence_list_construct(); // 各点を始点とする接続辺リストが構成される
   printf("出発点を入力してください\n");
   scanf("%d", &start);
   printf("出発点 = %d \n", start); // startからすべての点が到達可能であると仮定
   shortest_path_tree_construct(); // startを根とする最短パス木が構成される
   shortest_path_output();                               
   return 0;
}                                                   
