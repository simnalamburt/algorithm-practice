c,I,J;
char *B,*W;
N(n,s){
  n=0;
  s=1;
  for(;;){
    c=B[I++];
    if(c<45)return s*n;
    c==45?s=-1:(n=10*n+c-48);
  }
}
P(n,b){
  n/10?P(n/10,0):0;
  n||b?W[J++]=n%10+48:0;
}

main;__libc_start_main(T){
  char m[1<<12],w[1<<12];
  B=m;
  read(0,B,1<<12);
  W=w;

  T=N();
  while(T--){
    int x=N(),y=N(),X=N(),Y=N(),n=N(),S=0;
    while(n--){
      int u=N(),v=N(),r=N();
      S+=((x-u)*(x-u)+(y-v)*(y-v)<r*r)!=((X-u)*(X-u)+(Y-v)*(Y-v)<r*r);
    }
    P(S,1);
    W[J++]=10;
  }

  write(1,W,J);
  _exit(0);
}
