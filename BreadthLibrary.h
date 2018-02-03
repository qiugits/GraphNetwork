// 幅優先探索ライブラリプログラムBreadthLibrary.h
#define unvisited          -1
int parent[vmaxsize+1], blabel[vmaxsize+1], queue[vmaxsize+1];
int k;  // kは幅優先順のラベル
int front, rear; // frontとrearはそれぞれキューの先頭と末尾を指す
void bfs(int v){// vからの幅優先探索を行う関数
    int a, w;
    a = edgefirst[v];
    while (a != 0) {
        w = head[a];
        if (blabel[w] == unvisited) {// wにラベルがまだ付けられていないとき
            k++;
            blabel[w] = k;  // wに幅優先順のラベルkを付ける
            parent[w] = v;
            rear++;
            queue[rear] = w;
        }
        a = edgenext[a];
    }
}
void breadth_first(void){
    int v, v1;
    k = 0;
    for (v = 1; v <= n; v++) blabel[v] = unvisited;
       // どの点もラベルが付けられていない
    for (v = 1; v <= n; v++) {
        if (blabel[v] == unvisited) {
            // 点vにラベルが付けられていないときはvからの幅優先探索を開始する
            parent[v]=0; 
            k++;
            blabel[v] = k;  // vに幅優先順のラベルkを付ける
            rear = 1;
            front = 0;
            queue[rear] = v;
            while (front < rear) {// キューが空でない限り
                front++;
                v1 = queue[front]; // キューの先頭からv1を削除
                bfs(v1);  // v1からの幅優先探索の呼び出し
            }
        }
    }
}
void breadth_first_output(void){// 幅優先探索の結果を出力する関数
    int v;
    printf("\n");
    printf("　　点:    幅優先順      親\n");
    for (v = 1; v <= n; v++) {
        printf("%6d: %9d %9d\n", v, blabel[v], parent[v]);
    }
}
