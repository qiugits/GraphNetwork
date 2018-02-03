// 最長パス木を求めるプログラム longestpath.c
#include <stdio.h>
#define vmaxsize         1000
#define emaxsize         2000
#define unvisited          -1
#include"DiNetworkInput.h"
#include"CompStructLibrary.h"
#include"DepthLibrary.h"
int tprank[vmaxsize+1], tporder[vmaxsize+1];
int dmax[vmaxsize+1], path[vmaxsize+1];
int s;
void tpsort(void){// トポロジカルソートをする関数
    // 出発点sからすべての点が到達可能であることを仮定している
    int a, j, k, v;
    for (v = 1; v <= n; v++) {// 式(4.1)に基づいてvのtprankを決定
       j=n+1-postlabel[v];
       tprank[v]=j;
       tporder[j]=v;  // トポロジカルソートでj番目の点はvと記憶する
    }
    printf("\n 点v (tprank[v]): vを始点とする辺の終点w(tprank[w])のリスト\n");
    for (v = 1; v <= n; v++) {
        printf("%3d (%3d):  ", v, tprank[v]);
        a = edgefirst[v];
        k = 0;
        while (a != 0) {
            printf("%3d (%3d)  ", head[a],tprank[head[a]]);
            k++;
            if (k % 10 == 0) printf("\n    ");
            a = edgenext[a];
        }
        printf("\n");
    }
}
void longestpath_from(int s){// sからの到達可能な点への最長パスを計算する関数
    int a, j, v, w;
    dmax[s]=0;  // sからsへの最長パスの長さは0である
    path[s]=0;  // sからの到達可能な点への最長パス木の根がsである
    for (j = 1; j <= n; j++) {// トポロジカルソートに基づいて
        v= tporder[j]; 
        // sからvまでの最長パスの長さdmax[v]とパス上でvの直前の点path[v]の計算
        a=revedgefirst[v]; // vを終点とする辺のリストの先頭の辺がaである
        w=tail[a];         // wはaの始点
        dmax[v]=dmax[w]+length[a]; // 式(4.2)に基づくdmax[v]の初期設定
        path[v]=w;                 // 式(4.2)に基づくpath[v]の初期設定
        a=revedgenext[a];  // aの次の辺をaとする
        while (a != 0) {// vを終点とする辺のリストの末尾の辺になるまで繰り返す
            w=tail[a];  // wはaの始点
            if (dmax[v] < dmax[w]+length[a]){// wを経由したほうがより長いとき
                dmax[v] = dmax[w]+length[a]; // wを経由するほうに更新する
                path[v]=a;                   // aに更新する
            }
            a=revedgenext[a]; // aの次の辺をaとする
        }
    }
}
void longestpath_output(void){// sからすべての点への最長パスを出力する関数
    int v, j;
    printf("\n出発点%2dからのすべての点への最長パス\n",s);
    for (j = 1; j <= n; j++) {// トポロジカルソートに基づいて
       v=tporder[j]; 
       printf("%3dから%3dまでの距離は%4dであり%3dの直前の点は%3dです\n",
               s,v,dmax[v],v,tail[path[v]]);
    }
}
int main(void){
    directed_network_input(); 
    // 有向ネットワークの辺数m，点数n，各辺の始点，終点，長さが決定される
    dicomp_incidence_list_construct(); // 接続辺リストが構成される
    printf("出発点を入力してください\n");
    scanf("%d", &s);
    printf("出発点 = %d \n", s); // sからすべての点が到達可能であることを仮定
    depth_first(); // 深さ優先探索をして後行順ラベルを求める
    tpsort(); // トポロジカルソートを行う（tporder[1]==sとなることを仮定）
    longestpath_from(s);// sからの到達可能な点への最長パスが計算される
    longestpath_output();// sからの到達可能な点への最長パスが出力される
    return 0;
}
