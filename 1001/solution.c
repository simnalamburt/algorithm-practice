n;main;__libc_start_main(){read(0,&n,3);n=n%64-(n>>16);n=(n<0?write(1,"-",1),-n:n)+48;write(1,&n,1);_exit(0);}
