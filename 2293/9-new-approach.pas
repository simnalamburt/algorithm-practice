// fpc 9-new-approach.pas -O2 -Coti -vwnh
type
  u32 = Cardinal;
var
  coins_count, target, i, coin, current: u32;
  cases: array[0..10000] of u32;
begin
  read(coins_count, target);

  // Initialize 'cases' array
  cases[0] := 1;
  for i := 1 to target do begin
    cases[i] := 0;
  end;

  // Perform DP
  for i := 1 to coins_count do begin
    read(coin);
    for current := coin to target do begin
      cases[current] += cases[current - coin]
    end
  end;
  writeln(cases[target])
end.
