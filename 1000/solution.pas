{ fpc solution.pas -O2 -Co -Ct -Ci }

program main;
var
  a, b: integer;

begin
  readln(a, b);
  writeln(a + b)
end.
