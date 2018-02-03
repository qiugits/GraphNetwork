// 有向グラフ入力のライブラリプログラム DiNetworkInput.h
int tail[emaxsize+1], head[emaxsize+1], length[emaxsize+1];
int m, n;
void directed_network_input(void){// 有向ネットワークのデータを入力する関数
    int a;
    printf("入力するデータは有向グラフのデータです\n");
    printf("有向グラフの点数nと辺数mを入力してください\n");
    scanf("%d %d", &n, &m);
    printf("m本の各辺の始点と終点および重みを入力してください\n");
    for (a = 1; a <= m; a++) scanf("%d %d %d", &tail[a], &head[a], &length[a]);
    printf("有向グラフの点数n=%d，辺数 m=%d \n",n,m);
}
