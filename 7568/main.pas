// fpc main.pas -O2 -Coti -vwnh

type
  u8 = Byte;
var
  count, weight, height, rank, i, j: u8;
  weights: Array[0..49] of u8;
  heights: Array[0..49] of u8;
begin
  // Read input
  read(count);
  for i := 0 to count-1 do begin
    read(weight, height);
    weights[i] := weight;
    heights[i] := height;
  end;

  // Calc
  for i := 0 to count-1 do begin
    rank := 1;
    for j := 0 to count-1 do begin
      if (weights[i] < weights[j]) and (heights[i] < heights[j]) then begin
        rank += 1
      end
    end;
    write(rank);
    if i = count-1 then begin
      writeln()
    end else begin
      write(' ')
    end
  end
end.
