N,i;main;__libc_start_main(a,b){
  char B[10100],*p=B;
  read(0,B,3);
  for(;;){
    if(*p<48)break;
    N=10*N+*p++-48;
  }

  for(a=1;a<=N;++a){
    for(b=0;b<N;++b)B[i++]=b<N-a?32:42;
    B[i++]=10;
  }

  write(1,B,i);
  _exit(0);
}
