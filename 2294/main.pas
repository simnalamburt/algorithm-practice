// fpc main.pas -O2 -Coti -vwnh
type
  u32 = Cardinal;
var
  coins_count, target, i, coin, current, candidate, answer: u32;
  counts: array[0..10000] of u32;
begin
  read(coins_count, target);

  // counts[x]: 현재까지 입력받은 동전들을 사용해, 'x원'을 만들고자 할 때 필요한
  // 최소 동전 수. 불가능한 경우 10000 초과의 값이 저장됨.
  counts[0] := 0;
  for i := 1 to target do begin
    counts[i] := 10001;
  end;

  // Perform DP
  for i := 1 to coins_count do begin
    read(coin);
    for current := coin to target do begin
      candidate := 1 + counts[current - coin];
      if counts[current] > candidate then begin
        counts[current] := candidate
      end
    end
  end;

  answer := counts[target];
  if answer > 10000 then begin
    writeln('-1')
  end else begin
    writeln(answer)
  end
end.
