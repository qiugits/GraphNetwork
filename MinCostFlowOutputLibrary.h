// 最小費用フロー出力のライブラリプログラム MinCostFlowOutputLibrary.h
void mincost_flow_output(void){
   int e, cap, value, totalcost;
   printf("\n");
   printf("\n入口%dから出口%dへの流量最大の最小費用フローf\n", s, t);
   value=0; totalcost=0;
   for (e = 1; e <= m; e++) {
      cap = rescap[2*e-1]+rescap[2*e];
      printf("辺%2d  始点%2d  終点%2d  費用%3d  容量%3d   f(%2d)=%2d \n", 
               e, head[2*e-1], head[2*e], cost[2*e], cap, e, rescap[2*e-1]);
      if (head[2*e-1] == s) value=value+rescap[2*e-1];
      totalcost=totalcost+cost[2*e]*rescap[2*e-1];
   }
   printf("最大フローfの流量 = %2d     fの費用 = %2d\n", value, totalcost);
}
void auxiliary_network_output(void){
   int e, cap, redcost;
   printf("\n");
   for (e = 1; e <= m; e++) {
      cap = rescap[2*e-1]+rescap[2*e];
      redcost=cost[2*e]+distance[head[2*e-1]]-distance[head[2*e]];
      printf("辺%2d  始点%2d  終点%2d  簡約費用%4d  容量%3d   f(%2d)=%2d \n", 
               e, head[2*e-1], head[2*e], redcost, cap, e, rescap[2*e-1]);
   }
}
