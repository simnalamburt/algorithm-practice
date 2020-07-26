#include<stdio.h>
#define X __builtin_popcountll
typedef long T;T N,A=0,B=-1,I[10];void c(T G){T U=0;for(T i=0;i<N;++i)if(G&(1<<i))U|=I[i];T b=X(G),a=X(U);if(a>A)A=a,B=b;else if(a==A&&b<B)B=b;}void f(T p,T G){if(!p){c(G);return;}f(p-1,G);f(p-1,G+(1<<(p-1)));}int main(){T M;scanf("%ld%ld",&N,&M);char z[M+1];for(T i=0;i<N;++i){scanf("%*s%s",z);T S=0;for(T n=0;n<M;++n)if(z[n]=='Y')S+=1ull<<n;I[i]=S;}f(N,0);printf("%ld\n",B);}
