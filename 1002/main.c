c;
N(n,s){
  n=0;
  s=1;
  for(;;){
    read(0,&c,1);
    // NOTE: 올바른 입력만 들어온다면, '0'보다 작은 글자는
    // 무조건 '-', ' ', '\n' 중 하나다
    if (c == '-') { s = -1; }
    else if (c < '0') { return s * n; }
    else { n = 10*n + c - '0'; }
  }
}

main(T,i){
  T=N();
  for(i=0;i<T;++i){
    int
      x1=N(),
      y1=N(),
      r1=N(),
      x2=N(),
      y2=N(),
      r2=N(),
      dd=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2),
      ib=(r1-r2)*(r1-r2),
      ob=(r1+r2)*(r1+r2),
      c;
    const char *s;
    dd == 0 && r1 == r2 ? (s="-1\n",c=3) :
      ib < dd && dd < ob ? (s="2\n",c=2) :
      dd == ib || dd == ob ? (s="1\n",c=2) :
      (s="0\n",c=2);
    write(1,s,c);
  }
}
