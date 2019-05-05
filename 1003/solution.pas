// fpc solution.pas -O2 -Coti -vwnh

function fibo(n: Int64): Int64;
var
  a: Int64 = 0;
  tmp: Int64;
begin
  if n = 0 then exit(0);
  if n = -1 then exit(1);
  fibo := 1;
  while n > 1 do begin
    tmp := a + fibo;
    a := fibo;
    fibo := tmp;
    n := n - 1;
  end
end;

var
  count: Int64;
  num: Int64;
begin
  readln(count);
  while count > 0 do begin
    readln(num);
    writeln(fibo(num-1), ' ', fibo(num));
    count := count - 1;
  end
end.
