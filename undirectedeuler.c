// 連結な無向オイラーグラフの一筆書きを求めるプログラムundirectedeuler.c
#include <stdio.h>
#define vmaxsize         1000
#define emaxsize         2000
#define e2maxsize        4000
#include"GraphInput.h"
#include"StandardStructLibrary.h"
int start;
int path[emaxsize+1];
void euler(void){
    int current[vmaxsize+1]; 
    int searched[emaxsize+1]; // searched[e]==1は無向辺eが探索済み
    int v, e, a,top,last;
    for (v = 1; v <= n; v++) current[v] = edgefirst[v];
    for (e = 1; e <= m; e++) searched[e] = 0;
    printf("出発点startを入力してください\n");
    scanf("%d", &start);
    printf("出発点startは%dです\n",start);
    v=start;
    top = 0; 
    last=m+1;
    a=current[v];  // aは点vを始点とする辺のリストの先頭の辺
    current[v]=edgenext[a];  // current[v]をリストでaの次の辺とする
    searched[(a+1)/2]=1; // aに対応する無向グラフの辺(a+1)/2を探索済みとする
    top=top+1;
    path[top]=a; // 一筆書きの最初の辺をaとする
    v=head[a];   // vはaの終点
    while (top != last-1){
        while (current[v] != 0 && searched[(current[v]+1)/2]!=0) 
            current[v]=edgenext[current[v]]; // 探索済みの無向グラフの辺を無視
        if (current[v] != 0){// 無向グラフの辺(current[v]+1)/2は未探索
            a=current[v];    // 辺aをたどる
            current[v]=edgenext[a]; // current[v]をリストでaの次の辺とする
            searched[(a+1)/2]=1; // 無向グラフの辺(a+1)/2は探索済みとする
            top=top+1;
            path[top]=a; // 一筆書きの次の辺をaとする
            v=head[a];   // vはaの終点
        }
        else {// current[v] == 0 vを始点とする辺のリストの最後の辺まで見終えた
            a=path[top];  // これまでたどったパスを未探索の辺をもつ点まで戻る
            top=top-1;
            last=last-1;
            path[last]=a; // 戻りながらたどった辺を後ろから詰め込む
            if (a % 2==0) v=head[a-1];
            else v=head[a+1]; // vは戻りながらたどった辺aの始点
        }
    }
}
void array_euler_output(void){// 一筆書きの結果の配列を出力
   int a,b,i;
    printf("\n一筆書き");
    printf("\n i番目");
    for (i=1; i<= m; i++) {printf("%3d",i);}
    printf("\n　　辺");
    for (i=1; i<= m; i++) {
       printf("%3d",(path[i]+1)/2);
    }
    printf("\n　始点");  
    for (i=1; i<= m; i++) {
        a=path[i];
        if (a % 2 == 0) b=a-1;
        else b=a+1;
       printf("%3d",head[b]);
    }
    printf("\n　終点");  
    for (i=1; i<= m; i++) {printf("%3d",head[path[i]]);}
    printf("\n");  
}
int main(void){
    graph_input(); // 無向グラフの辺数m，点数n，始点，終点が決定される
    incidence_list_construct(); // 接続辺リストが構成される
//    incidence_list_output();    // 構成された接続辺リストが出力される
    euler();
    array_euler_output(); // 一筆書きの結果の配列を出力
    return 0;
}
