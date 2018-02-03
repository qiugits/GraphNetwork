// ライブラリプログラム BigraphInConstruct.h
int tail[emaxsize+1], head[emaxsize+1];
int edgefirst[vmaxsize+1], edgenext[emaxsize+1];
int match[vmaxsize+1];  // 点vに接続するマッチングの辺match[v]
int m, n, n1, n2;       // 左側の点数n1，右側の点数n2，n=n1+n2
void bipartite_graph_input(void){
    int a;
    printf("入力するデータは二部グラフのデータです\n");
    printf("二部グラフの左側の点数n1，右側の点数n2，辺数mを入力してください\n");
    scanf("%d %d %d", &n1, &n2, &m);
    printf("m本の各辺の左端点と右端点を入力してください\n");
    n=n1+n2; // nはグラフの点数
    for (a = 1; a <= m; a++) {
        scanf("%d %d", &tail[a], &head[a]);
    }
    printf("二部グラフの左側の点数n1=%d，右側の点数n2=%d，辺数m=%d \n",n1,n2,m);
}
void bipartite_incidence_list_construct(void){
    int a, v1;
    for (v1 = 1; v1 <= n1; v1++) edgefirst[v1] = 0;
    for (a = m; a >= 1; a--) {
        v1 = tail[a];
        edgenext[a] = edgefirst[v1];
        edgefirst[v1] = a;
    }
}
void bipartite_incidence_list_output(void){
    int a, k, v1;
    printf("\n接続辺リスト　左側の点v1: 辺a （aの右側の点）の並び\n");
    for (v1 = 1; v1 <= n1; v1++) {
        printf("%3d:  ", v1);
        a = edgefirst[v1];
        k = 0;
        while (a != 0) {
            printf("%3d (%2d)", a,head[a]);
            k++;
            if (k % 12 == 0) printf("\n    ");
            a = edgenext[a];
        }
        printf("\n");
    }
}
void matching_output(void){
    int a, v1, k;
    printf("\n最大マッチング：   辺    左端点   右端点\n");
    k=0; 
    for (v1 = 1; v1 <= n1; v1++) {
        if (match[v1] != free) {
            k++;
            a=match[v1]; 
            printf("              %6d %8d %8d\n", a, tail[a], head[a]);
        }
    }
    printf("最大マッチングの辺数 %d \n",k);
}
