var s:String;i:Word;begin read(s);for i:=0to(length(s)+9)div 10-1do writeln(copy(s,i*10+1,10))end.
