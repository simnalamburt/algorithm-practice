#include <stdio.h>
#define X __builtin_popcountl
int main(){int N,M,A=0,B=-1,a,b,i,n,x;scanf("%d%d",&N,&M);long D[N],y,s;char z[M+1];for(i=0;i<N;++i){scanf("%*s%s",z);s=0;for(n=0;n<M;++n)if(z[n]=='Y')s+=1l<<n;D[i]=s;}for(x=0;x<1<<N;++x){y=0;for(int i=0;i<N;++i)if(x&(1<<i))y|=D[i];b=X(x);a=X(y);if(a>A)A=a,B=b;else if(a==A&&b<B)B=b;}printf("%d\n",B);}
