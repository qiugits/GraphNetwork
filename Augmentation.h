// ライブラリプログラム Augmentation.h
int parent[vmaxsize+1]; // 深さ優先探索木における点vの親parent[v]
int pathfound, pathend; // 増加パス（存在 (pathfound=true)，pathendは右側の点）
void bipartite_dfs(int v1){// 左側の点v1からの二部グラフでの深さ優先探索 
    int v2, w1;
    int a,b;
    a=edgefirst[v1]; // aはv1に接続する辺のリストの先頭の辺
    while (a != 0) {// v1に接続する辺のリストの最後の辺になるまで以下を繰り返す
        v2=head[a]; // aは左側の点v1から右側の点v2に向かう有向辺と見なす
        if (parent[v2]==unvisited && level[v2]==level[v1]+1) {
            parent[v2]=a; // aを右側の点v2から親の左側の点v1を指すと見なす
            if (level[v2] != max_level) {// v2は右側の点でマッチされている
                b=match[v2]; // マッチング辺はb
                w1=tail[b]; // bは右端点v2から左端点w1への仮想的な有向辺と見なす
                parent[w1]=b; // bは左側の点w1から親のv2を指す
                bipartite_dfs(w1);
            }
            else {// level[v2] == max_level
                if (match[v2]==free){// v2は右側の点でマッチされていない
                    pathend=v2; // 増加パスの終点はv2
                    pathfound=true; // 増加パス発見
                }
            }
        }
        if (pathfound) a=0; // 増加パス発見ならば強制終了へ
        else a=edgenext[a]; // 増加パス未発見ならば次の辺へ移る
    }
}
void augmentation(void){
    int v, v1, v2, w1;
    int a,b;
    for (v = 1; v <= n; v++) parent[v] = unvisited;
    for (v1 = 1; v1 <= n1; v1++) {
        if (match[v1] == free) {// v1はマッチされていない左側の点
            pathfound = false; // v1からの増加パスの探索
            parent[v1] = root;  // v1からの深さ優先探索木の根はv1
            bipartite_dfs(v1);  // v1からの深さ優先
            if (pathfound) { // v1からの深さ優先でpathendへの増加パス発見
                v2=pathend; // 深さ優先探索木でpathendから親を根v1までたどる
                a=parent[v2]; // たどりながらマッチング辺と非マッチング辺の交換
                match[v2]=a; 
                w1=tail[a]; 
                match[w1]=a;
                while (w1 != v1) {
                    b=parent[w1]; 
                    v2=head[b]; 
                    a=parent[v2]; 
                    match[v2]=a; 
                    w1=tail[a]; 
                    match[w1]=a;
                }
            }
        }
    }
}
