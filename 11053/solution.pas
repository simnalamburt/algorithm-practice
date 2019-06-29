type
  u16 = Word;
var
  len: u16 = 0;
  SEQ: Array[0..999] of u16;
  count, i, num, lo, hi, mid: u16;
begin
  read(count);
  for i := 0 to count - 1 do begin
    read(num);

    // Bisect
    lo := 0;
    hi := len;
    while lo < hi do begin
      mid := (lo + hi) div 2;
      if SEQ[mid] < num then
        lo := mid + 1
      else
        hi := mid
    end;

    if lo = len then len := len + 1;

    SEQ[lo] := num
  end;
  writeln(len)
end.
