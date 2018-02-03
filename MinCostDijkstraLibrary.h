// 最小費用フローアルゴリズムのDijkstra最短パスライブラリプログラム 
// MinCostDijkstraLibrary.h
int distance[vmaxsize+1]; 
int path[vmaxsize+1];
int shortest_path_tree_construct(int s){// startを根とする最短パス木の構成
   int heap[vmaxsize+1], inv_heap[vmaxsize+1];
   int distredcost[vmaxsize+1];
   int a, v, v1, v2, i, redcost;
   for (v = 1; v <= n; v++) path[v] = unvisited;
   distredcost[s]=0; // 出発点sからsまでの距離は0と初期設定
   path[s]=0;     // 出発点sは最短パス木の根に初期設定
   heap[1]=s;     // ヒープにsを挿入
   inv_heap[s]=1; // sのヒープでのノードは1と初期設定
   i=1; 
   t_found=false; 
   while (i > 0) {// ヒープが空になるまで以下を繰り返す
      v1=heap[1]; // VPに含まれない点で距離が最小の点をv1とする
      if (v1 == t) t_found=true; 
      heap[1]=heap[i]; // ヒープの最後のノードに記憶されている点を根に移す
      inv_heap[heap[1]]=1;
        // ヒープの根に記憶されている点にヒープでのノードが1（根）であるとする
      i=i-1; // ヒープのサイズを1減らす
      if (i > 1) shift_down(1,i,heap,inv_heap,distredcost); // iから下移動
      a=edgefirst[v1]; // aはv1を始点とする辺のリスト最初の辺
      while (a != 0) {// v1を始点とする辺のリストの最後の辺になるまで
         if (rescap[a]==0) a=edgenext[a]; // 残容量が0なら次の辺へ移る
         else {// 残容量は正
            v2=head[a];
            redcost=cost[a]+distance[v1]-distance[v2]; //辺aの簡約費用 
            if (path[v2]==unvisited) {// 辺aの終点がVPにないとき
               distredcost[v2]=distredcost[v1]+redcost;// v2までの暫定簡約距離
               path[v2]=a; // v2までのこれまでの最短パスの最後の辺はa
               i=i+1;    // ヒープのサイズを1増やしそこにv2を挿入する                                           
               heap[i]=v2;   // ヒープのノードiにv2を記憶する      
               inv_heap[v2]=i; 
                  // v2が記憶されているヒープのノードはiとしてv2に記憶     
               shift_up(i,heap,inv_heap,distredcost); // iからの上移動
            }
            else {
               if (distredcost[v2]>distredcost[v1]+redcost) {
                // より短いパスが発見された         
                  distredcost[v2]=distredcost[v1]+redcost;// こちらのパスに更新
                  path[v2]=a; // v2までの最短パスの最後の辺をaに更新する
                  shift_up(inv_heap[v2],heap,inv_heap,distredcost); 
                    // v2が記憶されているヒープのノードから上移動する          
               }
            }
            a=edgenext[a];
         }
      }
   }
   printf("\n");
   for (v = 1; v <= n; v++) {
      if (path[v] == unvisited) {
         printf("点%2d    簡約距離%3d    距離%3d \n", v, unvisited, unvisited);
      }
      else {
         distance[v]=distance[v]+distredcost[v];
         printf("点%2d    簡約距離%3d    距離%3d \n",v,distredcost[v],distance[v]);
      }
   }
   return(t_found);
}
