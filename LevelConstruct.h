// ライブラリプログラムLevelConstruct.h
int level[vmaxsize+1];  // レベルグラフにおける点vのレベルlevel[v]
int queue[vmaxsize+1];  // 幅優先探索のためのキュー
int max_level;          // マッチされていない右側の点の最小レベル
int t_found;            // マッチされていない右側の点へ到達したときt_found=true
int front, rear;        // キューの先頭frontと末尾rear
void bipartite_bfs(int v1){// 左側の点v1からの二部グラフでの幅優先探索
    int v2, w1;
//    int a;  この文を次の文に置き換える 
    int a,b;
    a=edgefirst[v1]; // aはv1に接続する辺のリストの先頭の辺
    while (a != 0) {// v1に接続する辺のリストの最後の辺になるまで以下を繰り返す
        v2 = head[a]; // aは左側の点v1から右側の点v2に向かう有向辺と見なす
        if (level[v2] == unvisited) {// v2は右側の点で初めて訪問
            level[v2] = level[v1]+1;
            if (t_found == n+2){// 増加パスはまだ見つかっていない
                if (match[v2] != free) {// v2はマッチされている
//                  a=match[v2]; // マッチング辺はa
//                  w1=tail[a];  // aは右端点v2から左端点w1への有向辺を見なす
//                  上の二つの文を以下の二つの文に置き換える 
                    b=match[v2]; // マッチング辺はb
                    w1=tail[b]; // bは右端点v2から左端点w1への有向辺を見なす
                    level[w1]=level[v1]+2; 
                    rear++; 
                    queue[rear]=w1;
                }
                else {// v2はマッチされていないのでv1からv2へのパスは増加パス
                    t_found=rear+1; // t_found<n+2 （増加パスが存在する）
                    max_level=level[v2];
                }
            }
        }// 右側の点v2が訪問済みのときには何も行わない
        a = edgenext[a]; // 次の辺へ移る
    }
}
void levelgraph(void){// レベルグラフの構成
    int v,v1;
    rear = 0;    // キューの初期化
    front = 1;
    t_found=n+2; // 増加パスはまだ発見されていないと初期設定
    for (v = 1; v <= n; v++) level[v] = unvisited; // どの点も未訪問と初期設定
    for (v1 = 1; v1 <= n1; v1++) {
        if (match[v1] == free) {// v1はマッチされていない左側の点
            level[v1] = 0; // v1からの二部グラフの幅優先探索が後で行われる
            rear++;
            queue[rear] = v1; //キューqueueの末尾にv1を挿入
        }
    }
    while (front < t_found) {// 増加パスはまだ発見されていない
        if (front <= rear) {// キューqueueは空でない限り繰り返す
            v1 = queue[front]; // キューから先頭の点v1を削除
            bipartite_bfs(v1); //v1からの二部グラフの幅優先探索開始
            front++;
        }
        else {// キューqueueは空であるので，whileループを強制終了する
            front=t_found;
        }
    }
}
