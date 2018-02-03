// 連結な有向オイラーグラフの一筆書きを求めるプログラム directedeuler.c
#include <stdio.h>
#define vmaxsize         1000
#define emaxsize         2000
#define true                1
#define false               0
#include"DigraphInput.h"
#include"DiStandStructLibrary.h"
int start;
int path[emaxsize+1];
void directeuler(void){
    int current[vmaxsize+1]; 
        // current[v]はvを始点とする辺リストで未探索の最初の辺
    int stack[emaxsize+1];
    int v,a,top,last;
    for (v = 1; v <= n; v++) current[v] = edgefirst[v];
    printf("出発点startを入力してください\n");
    scanf("%d", &start);
    printf("出発点startは%dです\n",start);
    v=start;
    last=m+1;
    top=0;
    a=current[v];  // 最初にたどる辺はa 
    current[v]=edgenext[a]; 
    //current[v]はvを始点とする辺のリストで次にたどる辺
    top=top+1;
    stack[top]=a; 
    //辺aを最初にたどりスタックstackにaを挿入（スタックの最初の辺）
    v=head[a]; //aの終点vへ進む
    while (top!=0){// スタックstackが空でない限り以下を繰り返す
        if (current[v] != 0) {// vを始点とする未探索の辺が存在する
            a=current[v]; //その辺をaとする
            current[v]=edgenext[a];
            top=top+1;
            stack[top]=a; //辺aを次にたどりスタックstackにaを挿入
            v=head[a]; //aの終点vへ進む
        }
        else {// vを始点とする未探索の辺が存在しなくなった
            a=stack[top]; //スタックの先頭から辺aを取り出す
            top=top-1;
            last=last-1;
            path[last]=a; 
            //解のオイラーツアーでたどることが未確定の辺で最後にたどる辺はa
            v=tail[a]; // vはスタックの先頭から取り出した辺aの始点
        }
    }
}
void directedeuler_output(void){// 一筆書きの結果の配列を出力
    int a,e;
    printf("\n一筆書き：   辺    始点   終点\n");
    for (e = 1; e <= m; e++) {
        a=path[e];
        printf("%6d: %6d %6d %6d\n", e, a, tail[a], head[a]);
    }
}
int main(void){
    directed_graph_input(); // 有向グラフの辺数m，点数n，始点，終点が決定される
       // 入力のグラフは連結な有向オイラーグラフであることが必要である
    distand_incidence_list_construct(); // 各点を始点とする接続辺リストが構成される
//  distand_incidence_list_output();    // 構成された接続辺リストが出力される
    directeuler();
    directedeuler_output();
    return 0;
}
