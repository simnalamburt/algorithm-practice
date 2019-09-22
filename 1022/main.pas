// fpc main.pas -O2 -Coti -vwnh

type
  u8 = Byte;
  i16 = SmallInt;
  u32 = Cardinal;
var
  x, x0, x1, y, y0, y1: i16;
  width, height, length: u8;
  biggest: u32;
  table: Array of Array of u32;
begin
  read(y0, x0, y1, x1);

  // 테이블 초기화
  width := x1 - x0 + 1;
  height := y1 - y0 + 1;
  setLength(table, height, width);
  for y := y0 to y1 do begin
    for x := x0 to x1 do begin
      if (-y < x) and (x <= y) then
        table[y - y0][x - x0] := (2*y + 1)*(2*y + 1) + x - y
      else if (x < y) and (y <= -x) then
        table[y - y0][x - x0] := (-2*x + 1)*(-2*x + 1) + 3*x + y
      else if (y < -x) and (-x <= -y) then
        table[y - y0][x - x0] := (-2*y + 1)*(-2*y + 1) + 5*y - x
      else if (-x < -y) and (-y <= x) then
        table[y - y0][x - x0] := (2*x + 1)*(2*x + 1) - 7*x - y
      else
        table[y - y0][x - x0] := 1
    end
  end;

  //// 가장 큰 숫자의 자리수가 몇인지 찾기
  biggest := 0;
  for y := 0 to height - 1 do begin
    for x := 0 to width - 1 do begin
      if biggest < table[y][x] then
        biggest := table[y][x]
    end
  end;
  length := 0;
  while biggest > 0 do begin
    biggest := biggest div 10;
    length += 1
  end;

  // 출력
  for y := 0 to height - 1 do begin
    for x := 0 to width - 1 do begin
      write(table[y][x]:length);
      if x < width - 1 then
        write(' ')
    end;
    writeln()
  end
end.
