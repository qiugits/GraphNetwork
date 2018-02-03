// 増加パスに沿ってフロー増加のライブラリプログラム MinCostFlowAugmentLibrary.h
void augmentation(void){
   int afwd, abk, v, w, delta, cap;
   counter++;
   afwd = path[t]; // Pの最後の辺はafwd
   abk = afwd+1; if (afwd % 2 ==0) abk = afwd-1;
      //abkはPの最後の辺afwdの逆向きの辺でtは辺abkの始点
   delta = rescap[afwd]; 
   v = head[abk]; // vはafwdの始点
   while (v != s) {// sに到達するまでPを逆にたどる
      afwd = path[v]; // afwdはvに入るP上の辺
      abk = afwd+1; 
      if (afwd % 2 ==0) abk = afwd-1; //abkは辺afwdの逆向きの辺
      v = head[abk]; // vはafwdの始点
      if (delta > rescap[afwd]) delta = rescap[afwd];
         // deltaは最終的にはdelta=Δ(P)となる
   }
   printf("\n");
   printf("Δ（P%d)= %d\n", counter,delta);
   v = t;
   while (v != s) {// 増加パスに沿ってdelta=Δ(P)だけフローを送り込む
      afwd = path[v]; 
      abk = afwd+1; 
      if (afwd % 2 ==0) abk = afwd-1; // abkはPの辺の逆向きの辺
      cap = rescap[afwd]+rescap[abk];
      rescap[afwd] = rescap[afwd]-delta;
      rescap[abk] = rescap[abk]+delta;
      if (afwd % 2 ==0) {// afwdはNの本来の辺
         printf("辺%2d  始点%2d  終点%2d  費用%3d  容量%3d   f(%2d):%2d --> %2d\n", 
                 afwd/2, head[abk], head[afwd], cost[afwd], cap, afwd/2, 
                 rescap[abk]-delta, rescap[abk]);
      }
      else {// afwdはNにはなかった仮想的な辺で本来の辺abkの逆向きの辺
         printf("辺%2d  始点%2d  終点%2d  費用%3d  容量%3d   f(%2d):%2d --> %2d\n", 
                 abk/2, head[afwd], head[abk], cost[abk], cap, abk/2, 
                 rescap[afwd]+delta, rescap[afwd]);
      }
      v = head[abk];
   }
}
