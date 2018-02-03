// Kruskalの最小全点木を求めるプログラム kruskal.c
#include <stdio.h>
#define vmaxsize         1000
#define emaxsize         3000
#define unvisited          -1
#define true                1
#define false               0
int tail[emaxsize+1], head[emaxsize+1], weight[emaxsize+1];
// ネットワークの各辺eの両端点tail[e]，head[e]と重みweight[w]を記憶するための配列
int order[emaxsize+1]; // 重みの小さい順に辺を記憶するための配列
int tree[vmaxsize+1]; // 最小全点木に含まれる辺を記憶するための配列
int size[vmaxsize+1], parent[vmaxsize+1]; // ユニオン・ファインド森のための配列
int m, n; // ネットワークの辺数mと点数nを記憶
void network_input(void){// ネットワークのデータを入力する関数
    int e;
    printf("入力するデータは連結な無向ネットワークのデータです\n");
    printf("無向グラフの点数nと辺数mを入力してください\n");
    scanf("%d %d", &n, &m);
    printf("m本の各辺の両端点と重みを入力してください\n");
    for (e = 1; e <= m; e++) scanf("%d %d %d", &tail[e], &head[e], &weight[e]);
    printf("無向グラフの点数n=%d，辺数 m=%d \n",n,m);
}
void heapify(int p, int q) {// 配列の番地pから番地qまでの部分をヒープとして構成
    int r,s;
    while (2*p <= q) {
        // ヒープのノードpを根とする部分木がq以下のノードを子としてもつ限り
        r=2*p; // rをpの左の子とする
        if (r+1 <= q && weight[order[r+1]] > weight[order[r]]) r=r+1;
        // pが右の子ももつときは重みの大きいほうをrをする
        if (weight[order[p]] < weight[order[r]]) {
        // pよりもrのほうが重いときにはpとrに割り当てられている辺を交換する 
            s=order[p]; order[p]=order[r]; order[r]=s; p=r;
        }
        else p=q; // 強制終了へ進む
    }
}
void heapsort(void) {// 重みの小さい順に辺をソーティングするヒープソート
    int e,temp;
    for (e = 1; e <= m; e++) order[e]=e;
    for (e = m/2; e >= 1; e--) heapify(e,m); // ヒープの構成
    for (e = m; e >= 2; e--) {// ヒープから最大重みの辺を削除
        temp=order[1]; order[1]= order[e]; order[e]=temp; 
           // 根の辺とヒープの最後の辺の交換
        heapify(1,e-1); // // ヒープの再構成
    }
} 
int find(int i) {// ユニオン・ファインド森でiを含む集合の発見
    int j;
    j=i; 
    while (parent[j] != j) j=parent[j];
    while (i != j) { parent[i]=j; i=parent[i]; }
    return j;
}
void set_union(int i, int j) {// ユニオン・ファインド森でiとjを含む集合の併合
    if (size[i]>=size[j]) {
       parent[j]=i; size[i]=size[i]+size[j]; 
    }
    else {
       parent[i]=j; size[j]=size[i]+size[j]; 
    }
}
void minimum_spanning_tree_construct(void){// 最小全点木を求める関数
    int e,v,v1,v2;
    int i, tree_size;
    for (v = 1; v <= n; v++) {// ユニオン・ファインド森の初期化
        parent[v]=v; size[v]=1; // 各ユニオン・ファインド木は1点からなる
    } 
    tree_size=0; // 最小全点木に含まれることが決定した辺の本数の初期化
    i=0;
    while (tree_size < n-1 && i<= m) {// n-1本の辺が最小全点木に含まれるまで
        i++; 
        e=order[i]; // 重みが次に小さい辺eに移る
        v1=find(tail[e]); // eの一方の端点を含む集合（ユニオン・ファインド木の根）
        v2=find(head[e]); // eの他方の端点を含む集合（ユニオン・ファインド木の根）
        if (v1 != v2) {// これらの集合が異なるときは併合する 
            tree_size++; // この辺eを最小全点木の辺として入れる
            tree[tree_size]=e; 
            set_union(v1,v2);
        }
    }
}
void minimum_spanning_tree_output(void){// 最小全点木を出力する関数
    int e,k;
    int total_weight=0;
    printf("\n最小全点木を構成する辺\n");
    for (k = 1; k <= n-1; k++) {
        e=tree[k]; 
        total_weight=total_weight+weight[e];
        printf("辺%2d=(%d,%d)  重み%2d\n", e, tail[e], head[e], weight[e]);
    }
    printf("最小全点木の重みは%dです\n", total_weight); 
}
int main(void){
    network_input(); // 辺数m，点数n，各辺の両端点と重みが決定される
    heapsort(); // 辺の重みの小さい順に並べるヒープソートが行われる
    minimum_spanning_tree_construct(); // 最小全点木を求める
    minimum_spanning_tree_output(); // 最小全点木を出力する
    return 0;
}
