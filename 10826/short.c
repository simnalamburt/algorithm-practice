#include <stdio.h>
#define Z (long)1E18
#define H short
#define Q long
typedef struct{H L;Q X[117];}I;void A(I*s,I*l,I*r){if(l->L<r->L){A(s,r,l);return;}s->L=l->L;Q c=0;for(H i=0;i<r->L;++i){Q n=l->X[i]+r->X[i]+c;s->X[i]=n%Z;c=n/Z;}for(H i=r->L;i<l->L;++i){Q n=l->X[i]+c;s->X[i]=n%Z;c=n/Z;}if(c){s->X[s->L++]=c;}}void S(I*s,I*p){s->L=p->L;for(H i=0;i<p->L;++i){s->X[i]=p->X[i];}}void P(I*s,FILE*f){if(!s->L){puts("0");return;}H D=(H)s->L-1;char M[18];for(H d=D;d>=0;--d){Q n=s->X[d];H j=17;for(;j>=0;--j){if(!n&&d==D){break;}M[j]="0123456789"[n%10];n/=10;}++j;fwrite(&M[j],1,18-j,f);}}int main(){int n;scanf("%d",&n);I a={0},b={1,{1}};while(n){I t;A(&t,&a,&b);S(&a,&b);S(&b,&t);--n;}P(&a,stdout);puts("");}