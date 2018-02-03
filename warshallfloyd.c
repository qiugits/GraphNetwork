// 全点間の最短パスを求めるWarshall-Floyd法 warshallfloyd.c
#include <stdio.h>
#define vmaxsize          100
#define maxvalue         1000
#define root                0
#define undefined          -1
int length[vmaxsize+1][vmaxsize+1]; // 式(9.1)を表す入力の初期距離行列
int dist[vmaxsize+1][vmaxsize+1];   // 式(9.1)を表す漸化式の距離行列D
int path[vmaxsize+1][vmaxsize+1];   // パス行列P
int n,m;
void network_input(void){// ネットワーク情報を読み込み行列lengthとpathの初期化
   int i,j;
   int a;
   int d;
   printf("入力するデータは有向ネットワークのデータです\n");
   printf("有向ネットワークの点数nと辺数mを入力してください\n");
   scanf("%d %d", &n, &m);
   for (i = 1; i <= n; i++) {
      for (j = 1; j <= n; j++) {
         length[i][j]=maxvalue;
         path[i][j]=undefined;
      }
      length[i][i]=0; 
      path[i][i]=root;
   }
   printf("m本の各辺の始点と終点および長さを入力してください\n");
   for (a = 1; a <= m; a++) {
      scanf("%d %d %d", &i, &j, &d);
      length[i][j]=d; 
      path[i][j]=i;
   }
   printf("有向ネットワークの点数n=%d，辺数 m=%d \n",n,m);

}
void distance_matrix_output(int k){// k回目の反復終了後の距離行列とパス行列の出力
   int i,j;
   printf("\n距離行列 D[%d]\n",k+1);
   for (i = 1; i <= n; i++) {
      for (j = 1; j <= n; j++) {
         printf("%6d",dist[i][j]);
      }
      printf("\n");
   }
   printf("\nパス行列 P[%d]\n", k+1);
   for (i = 1; i <= n; i++) {
      for (j = 1; j <= n; j++) {
         printf("%4d",path[i][j]);
      }
      printf("\n");
   }
}
int main(void){
   int i,j,k;
   network_input(); 
   // 有向ネットワークの辺数m，点数n，各辺の始点，終点，長さが決定される
   for (i = 1; i <= n; i++) { // 距離行列Dとパス行列の初期化
      for (j = 1; j <= n; j++) {
         dist[i][j]=length[i][j];
      }
   }
   distance_matrix_output(0);// 初期化された距離行列Dとパス行列の出力
   for (k = 1; k <= n; k++) {// k回目の反復
      for (i = 1; i <= n; i++) {//    点iから
         for (j = 1; j <= n; j++) {// 点jへのパスに対して
            if (dist[i][j] > dist[i][k]+dist[k][j]) {// より短いパスが発見された
               dist[i][j] = dist[i][k]+dist[k][j]; // 距離の更新
               path[i][j]=path[k][j]; // 最短パスの最後の辺の更新  
            }
         }
      }
      distance_matrix_output(k); // k回目の反復終了後の距離行列とパス行列の出力
   }
   return 0;
}                                                                   
