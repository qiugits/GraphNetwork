// 有向グラフの後行順ソートライブラリプログラム PostLibrary.h
#define unvisited          -1
#define visited             1
int order[vmaxsize+1], prelabel[vmaxsize+1];
   // order[j] = vのようにして後行順でj番目の点がvであることを表すための配列
int j;  // jは後行順のラベル
void post(int v){// vからの深さ優先探索で後行順ソートを行う再帰的な関数
    int a, w;
    prelabel[v] = visited; // vに訪問済みのラベルを付ける
    a = edgefirst[v]; // aはvを始点とする辺のリストの先頭の辺
    while (a != 0) {// aがvを始点とする辺のリストの最後になるまで
        w = head[a];  // aの終点をwとする
        if (prelabel[w] == unvisited) {// wが訪問済みでないとき
            post(w);  // wからの深さ優先探索の再帰呼び出し
        }
        a = edgenext[a]; // vを始点とする辺のリストでaの次の辺をaをする
    } // vからの深さ優先探索の終了
    j++;
    order[j] = v; // 後行順でj番目の点がvである
}
void postsort(void){// 後行順にソートする関数
    int v;
    for (v = 1; v <= n; v++) prelabel[v] = unvisited;
    j = 0;
    for (v = 1; v <= n; v++) 
        if (prelabel[v] == unvisited) post(v);
            // 点vにラベルが付けられていないときはvからの深さ優先探索を開始する
}
