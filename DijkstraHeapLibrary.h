// Dijkstraの最短パスでのヒープ操作ライブラリプログラム DijkstraHeapLibrary.h
void shift_down(int p, int q, int heap[], int inv_heap[], int distance[]) {
    // 配列heapの番地pから番地qまで下移動に基づいてヒープ構成
    int r,v;
    while (2*p <= q) {
        // ヒープのノードpを根とする部分木がq以下のノードを子としてもつ限り
        r=2*p; // rをpの左の子とする
        if (r+1<=q && distance[heap[r+1]] < distance[heap[r]]) r=r+1;
        // pが右の子ももつときは距離の小さいほうをrをする
        if (distance[heap[p]] > distance[heap[r]]) {
        // pよりもrのほうが小さいときにはpとrに割り当てられている点を交換する 
            inv_heap[heap[r]]=p; 
            inv_heap[heap[p]]=r; 
            v=heap[p]; 
            heap[p]=heap[r]; 
            heap[r]=v; 
            p=r; // pを子のノードrとして下移動する
        }
        else p=q; // 強制終了へ進む
    }
}
void shift_up(int p, int heap[], int inv_heap[], int distance[]) {
    // 配列heapの番地pからの上移動に基づいてヒープ構成
    int r,v;
    while (p > 1) {// pが根でない限り
        r=p/2;   // rをpの親とする
        if (distance[heap[p]] < distance[heap[r]]) {
        // rよりもpのほうが小さいときにはpとrに割り当てられている点を交換する 
            inv_heap[heap[r]]=p; 
            inv_heap[heap[p]]=r;
            v=heap[p]; 
            heap[p]=heap[r]; 
            heap[r]=v; 
            p=r; // pを親のノードrとして上移動する
        }
        else p=1; 
    }
}
