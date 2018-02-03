// 標準的データ構造構成のライブラリプログラムStandardStructEx.h
int edgefirst[vmaxsize+1];
int edgenext[e2maxsize+1];
void incidence_list_construct(void){// 接続辺リストを構成する関数
    int a, a2, v, v1, v2;
    for (v = 1; v <= n; v++) edgefirst[v] = 0; // 空のリストに初期設定
    for (a = m; a >= 1; a--) {// 辺aを逆順に見ていきながら
        a2 = a * 2;  // aを両方向の辺a2とa2-1としてaの両端点のリストに挿入
        v1 = head[a2-1]; // 点v1に接続する辺のリストの先頭にa2を挿入
        edgenext[a2] = edgefirst[v1];
        edgefirst[v1] = a2;
        v2 = head[a2];   // 点v2に接続する辺のリストの先頭にa2-1を挿入
        edgenext[a2-1] = edgefirst[v2];
        edgefirst[v2] = a2-1;
    }
}
void incidence_list_output(void){// 接続辺リストを出力する関数
    int a, k, v;
    printf("\n各点に接続する辺のリスト\n");
    printf("点v: vに接続する無向グラフの辺（vを始点とする有向グラフの辺）の並び\n");
    for (v = 1; v <= n; v++) {// 各点に接続する辺のリストの出力
        printf("%3d:  ", v);
        a = edgefirst[v];
        k = 0;
        while (a != 0) {
            printf("%3d (%3d)  ", (a+1)/2, a);
            k++; if (k % 10 == 0) printf("\n    ");
            a = edgenext[a];
        }
        printf("\n");
    }
}
void outputarray(void){// 標準的データ構造の配列の内容を出力
   int i;
   printf("\n番地");
   for (i=1; i<= 2*m; i++) {printf("%3d",i);}
   printf("\nhead");  
   for (i=1; i<= 2*m; i++) {printf("%3d",head[i]);}
   printf("\n");  
   printf("\n番地     ");
   for (i=1; i<= n; i++) {printf("%3d",i);}
   printf("\nedgefirst");  
   for (i=1; i<= n; i++) {printf("%3d",edgefirst[i]);}
   printf("\n");  
   printf("\n番地    ");
   for (i=1; i<= 2*m; i++) {printf("%3d",i);}
   printf("\nedgenext");  
   for (i=1; i<= 2*m; i++) {printf("%3d",edgenext[i]);}
   printf("\n");  
}
