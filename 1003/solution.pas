var n,x,a,b,t:Int64;begin read(n);while n>0do begin read(x);if x=0then writeln('1 0')else begin a:=0;b:=1;while x>1do begin t:=a+b;a:=b;b:=t;x:=x-1;end;writeln(a,' ',b)end;n:=n-1;end end.
