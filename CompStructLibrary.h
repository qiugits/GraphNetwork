// 完備データ構造構成のライブラリプログラムCompStructLibrary.h
int edgefirst[vmaxsize+1], revedgefirst[vmaxsize+1];
int edgenext[emaxsize+1], revedgenext[emaxsize+1];
void dicomp_incidence_list_construct(void){// 接続辺リストを構成する関数
    int a, v;
    for (v = 1; v <= n; v++) {// 空のリストに初期設定
        edgefirst[v] = 0; revedgefirst[v] = 0;
    }
    for (a = m; a >= 1; a--) {// 辺aを逆順に見ていきながら
        v = tail[a];  // vを始点とする辺のリストの先頭に辺aを挿入
        edgenext[a] = edgefirst[v];
        edgefirst[v] = a;
        v = head[a]; // vを終点とする辺のリストの先頭に辺aを挿入
        revedgenext[a] = revedgefirst[v];
        revedgefirst[v] = a;
    }
}
void dicomp_incidence_list_output(void){// 接続辺リストを出力する関数
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
    printf("\n各点を終点とする辺のリスト\n");
    printf("点v: vを終点とする辺（その始点）の並び\n");
    for (v = 1; v <= n; v++) {// 各点vを終点とする辺のリストの出力
        printf("%3d:  ", v);
        a = revedgefirst[v];
        k = 0;
        while (a != 0) {
            printf("%3d (%3d)  ", a, tail[a]);
            k++;
            if (k % 10 == 0) printf("\n    ");
            a = revedgenext[a];
        }
        printf("\n");
    }
}
