n;main;__libc_start_main(){read(0,&n,3);n=n%256-n/65536;if(n<0){write(1,"-",n<0);n=48-n;}else{n+=48;}write(1,&n,1);_exit(0);}
