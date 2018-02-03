// 標準的データ構造構成のライブラリプログラムDiStandStructLibrary.h
int edgefirst[vmaxsize+1];
int edgenext[emaxsize+1];
void distand_incidence_list_construct(void){// 各点を始点とする接続辺リストの構成
    int a, v;
    for (v = 1; v <= n; v++) edgefirst[v] = 0; // 空のリストに初期設定
    for (a = m; a >= 1; a--) {// 辺aを逆順に見ていきながら
        v = tail[a];  // vを始点とする辺のリストの先頭に辺aを挿入
        edgenext[a] = edgefirst[v];
        edgefirst[v] = a;
    }
}
void distand_incidence_list_output(void){// 各点を始点とする接続辺リストの出力
    int a, k, v;
    printf("\n各点を始点とする辺のリスト\n");
    printf("点v: vを始点とする辺（その終点）の並び\n");
    for (v = 1; v <= n; v++) {// 各点vを始点とする辺のリストの出力
        printf("%3d:  ", v);
        a = edgefirst[v];
        k = 0;
        while (a != 0) {
            printf("%3d (%3d)  ", a, head[a]);
            k++; if (k % 10 == 0) printf("\n    ");
            a = edgenext[a];
        }
        printf("\n");
    }
}
