var x,a,b,t:Int64;begin read(x);a:=0;b:=1;while x>0do begin t:=a+b;a:=b;b:=t;x:=x-1;end;writeln(a)end.
