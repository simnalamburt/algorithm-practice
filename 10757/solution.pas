procedure add_then_print(
  a, b: AnsiString;
  len_a, len_b: Int64);
var
  buffer: Array Of Byte;
  delta, i: Int64;
  x, y, added, carry: Byte;
begin
  // len_a >= len_b
  delta := len_a - len_b;
  carry := 0;
  setlength(buffer, len_a);
  for i := len_a downto delta + 1 do begin
    x := ord(a[i]) - 48;
    y := ord(b[i - delta]) - 48;
    added := x + y + carry;

    carry := added div 10;
    buffer[i-1] := added mod 10;
  end;
  for i := delta downto 1 do begin
    x := ord(a[i]) - 48;
    added := x + carry;

    carry := added div 10;
    buffer[i-1] := added mod 10;
  end;
  if carry > 0 then write(carry);
  for i := 0 to len_a - 1 do begin
    write(buffer[i]);
  end;
  write(#10);
end;

var
  line: AnsiString;
  len, len_a, len_b: Int64;
begin
  read(line);
  len := length(line);
  len_a := pos(' ', line) - 1;
  len_b := len - 1 - len_a;

  if len_a >= len_b then
    add_then_print(copy(line, 1, len_a), copy(line, len_a + 2, len), len_a, len_b)
  else
    add_then_print(copy(line, len_a + 2, len), copy(line, 1, len_a), len_b, len_a)
end.
