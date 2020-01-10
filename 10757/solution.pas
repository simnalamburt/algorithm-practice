// TODO: Remove me
uses sysutils;

type
  bool = Boolean;
  i16 = Word;
  i32 = Int32;
  i64 = Int64;
  u64 = QWord;

const
  RADIX = 1000000000000000000;
  RADIX_COUNT = 18;

function find_begin(a: u64): u64;
begin
  if a >= RADIX_COUNT then
    find_begin := a - RADIX_COUNT + 1
  else
    find_begin := 1
end;

procedure add_then_print(
  a, b: AnsiString;
  len_a, len_b: u64);
var
  buffer: Array[0..556] Of u64; // 한칸당 RADIX_COUNT자리 10진수 하나
  buffer_idx: i32 = 0;
  buffer_size: i32;
  carry: u64 = 0;
  i: i64;
  begin_a, begin_b, delta, x, y, added: u64;
  _: i16;
  pad_zero: bool = false;
begin
  // len_a >= len_b
  i := len_a;
  delta := len_a - len_b;
  while i > delta do begin
    begin_a := find_begin(i);
    begin_b := find_begin(i - delta);
    val(copy(a, begin_a, i + 1 - begin_a), x, _);
    val(copy(b, begin_b, i + 1 - delta - begin_b), y, _);
    added := x + y + carry;

    if added >= RADIX then begin
      carry := 1;
      added -= RADIX;
    end else begin
      carry := 0;
    end;
    buffer[buffer_idx] := added;
    buffer_idx += 1;

    i -= RADIX_COUNT;
  end;
  while i > 0 do begin
    val(copy(a, i, find_begin(i)), x, _);
    added := x + carry;

    if added >= RADIX then begin
      carry := 1;
      added -= RADIX;
    end else begin
      carry := 0;
    end;
    buffer[buffer_idx] := added;
    buffer_idx += 1;

    i -= RADIX_COUNT;
  end;
  if carry > 0 then begin
    write(carry);
    pad_zero := true;
  end;
  buffer_size := buffer_idx;
  for buffer_idx := buffer_size - 1 downto 0 do begin
    if pad_zero then begin
      write(Format('%.18U', [buffer[buffer_idx]]));
    end else begin
      write(buffer[buffer_idx]);
      pad_zero := true;
    end;
  end;
  write(#10);
end;

var
  line: AnsiString;
  len, len_a, len_b: u64;
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
