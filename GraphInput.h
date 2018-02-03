// 無向グラフ入力のライブラリプログラムGraphInput.h
int head[e2maxsize+1];
int m, n;
void graph_input(void){// 無向グラフのデータを入力する関数
    int a, a2;
    printf("入力するデータは無向グラフのデータです\n");
    printf("無向グラフの点数nと辺数mを入力してください\n");
    scanf("%d %d", &n, &m);
    printf("m本の各辺の両端点を入力してください\n");
    for (a = 1; a <= m; a++) {
        a2 = a * 2;
        scanf("%d %d", &head[a2-1], &head[a2]);
    }
    printf("無向グラフの点数n=%d，辺数 m=%d \n",n,m);
}
