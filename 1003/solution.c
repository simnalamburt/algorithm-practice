c,I,J;
char *B,*W;
N(n){
  n=0;
  for(;;){
    c=B[I++];
    if(c<48)return n;
    n=10*n+c-48;
  }
}
P(n,b){
  n/10?P(n/10,0):0;
  n||b?W[J++]=n%10+48:0;
}

main;__libc_start_main(T,i,n,a,b,t){
  char m[1<<12],w[1<<12];
  B=m;
  read(0,B,1<<12);
  W=w;

  T=N();
  for(i=0;i<T;++i){
    for(n=N(),a=1,b=0;n>0;--n){
      t=a+b;
      a=b;
      b=t;
    }
    P(a,1);
    W[J++]=32;
    P(b,1);
    W[J++]=10;
  }

  write(1,W,J);
  _exit(0);
}
