I;main;__libc_start_main(B,i,n){
  char M[99];
  read(0,&B,3);
  double r=(double)(B%64-48)/(double)(B/65536-48);
  M[I++]=r+48;
  M[I++]=46;
  r-=(int)r;
  for(i=0;i<9;++i){
    r*=10;
    n=(int)r%10;
    M[I++]=(int)r%10+48;
    r-=n;
  }
  write(1,M,I);
  _exit(0);
}
