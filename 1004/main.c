#include <stdio.h>

int main() {
  int T;
  scanf("%d", &T);

  while(T--){
    int x,y,X,Y,n,S=0;
    scanf("%d%d%d%d%d",&x,&y,&X,&Y,&n);
    while(n--){
      int u,v,r;
      scanf("%d%d%d",&u,&v,&r);
      S+=((x-u)*(x-u)+(y-v)*(y-v)<r*r)!=((X-u)*(X-u)+(Y-v)*(Y-v)<r*r);
    }
    printf("%d\n",S);
  }
}
