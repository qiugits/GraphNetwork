// 強連結成分分解ライブラリプログラム StrongCompLibrary.h
// #define unvisited          -1
int vcomp[vmaxsize+1];
int vcompfirst[vmaxsize+1], vcompnext[vmaxsize+1];
    // 同一の強連結成分内の点のリスト表現のための配列
int ecomp[emaxsize+1];
int ecompfirst[vmaxsize+1], ecompnext[emaxsize+1];
    // 同一の強連結成分内の辺のリスト表現のための配列
int compmax; // compmaxは強連結成分の個数
void dfs_stcomp(int v, int k){
    // vからの深さ優先探索で対象の強連結成分に含まれる点を決定する再帰的な関数
    int w, a;
    vcomp[v]=k;        // vはk番目の強連結成分の点
    a=revedgefirst[v]; // vを終点とする辺のリストの先頭の辺がaである
    while (a != 0) {// vを終点とする辺のリストの末尾の辺になるまで繰り返す
        w=tail[a];  // wはaの始点
        if (vcomp[w]==unvisited) // wが訪問済みでないときはwをk番目の強連結成分に
            dfs_stcomp(w,k); // wからの深さ優先探索の再帰呼び出し
            // wが訪問済みのときにはwはすでに得られたいずれかの強連結成分の点
        a=revedgenext[a]; // aの次の辺をaとする
    }
}
int depth_first_stcomp(void){
    // 各点vに対してvがk番目の強連結成分に属するときvcomp[v]=kとする
    int j, k, v;
    k=0; 
    for (v = 1; v <= n; v++) vcomp[v] = unvisited; // vが属する強連結成分は未定
    for (j = n; j >= 1; j--) {// 後行順の逆順に強連結成分を求める
        v= order[j];
        if (vcomp[v]==unvisited){// 新しい強連結成分の最初の点がvである
            k++;                 // 新しい強連結成分はk番目の強連結成分
            dfs_stcomp(v,k);       // k番目の強連結成分に含まれる点をすべて求める
        }
    }
    return k; // このkは強連結成分の個数compmaxになる
}
void stcomp_construct(void){// 各強連結成分に含まれる点と辺のリストを構成する関数
    int a,h,k,v;
    compmax=depth_first_stcomp();  // 強連結成分の個数
    for (k = 1; k <= compmax; k++) {// k番目の強連結成分に含まれる点と辺のリスト
        vcompfirst[k]=0; // k番目の強連結成分に含まれる点のリストの初期化
        ecompfirst[k]=0; // k番目の強連結成分に含まれる辺のリストの初期化
    }
    for (v = n; v >= 1; v--) {
        k=vcomp[v];    // k番目の強連結成分に含まれる点のリストの先頭にvを挿入
        vcompnext[v]=vcompfirst[k];
        vcompfirst[k]=v;
    }
    for (a = m; a >= 1; a--) {
        k=vcomp[tail[a]];  // aの始点はk番目の強連結成分の点
        h=vcomp[head[a]];  // aの終点はh番目の強連結成分の点
        if (k==h) {// aの始点と終点は同一の強連結成分に含まれる
            ecomp[a]=k; // aはk番目の強連結成分の辺
            // k番目の強連結成分に含まれる辺のリストの先頭にaを挿入
            ecompnext[a]=ecompfirst[k];
            ecompfirst[k]=a;
        }
        else ecomp[a]=0;   // aは強連結成分に含まれない辺
    }
}
void stcomponent_output(void){
    int a,v,k,kk;
    for (k = 1; k <= compmax; k++) {
        kk=0;
        printf("\n");
        printf("強連結成分[%d]:  点部分集合 = {",k);
        v=vcompfirst[k];
        while (v != 0) {
            printf("%3d", v);
            kk++;
            if (kk % 10 == 0) printf("\n           ");
            v=vcompnext[v];
        }
        printf(" }\n");
        a= ecompfirst[k];
        while (a != 0) {
            printf("辺%3d:   始点%3d    終点%3d\n", a, tail[a],head[a]);
            a=ecompnext[a];
        }
    }
}
