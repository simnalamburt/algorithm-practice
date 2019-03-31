// fpc solution.pas -O2 -Coti -vwnh
//
// Reference: https://www.acmicpc.net/problem/1026

type
  i8 = ShortInt;
  i16 = SmallInt;
  i32 = LongInt;
  i64 = Int64;
  u8 = Byte;
  u16 = Word;
  u32 = Cardinal;
  f32 = Single;
  f64 = Double;
  IntArray = Array of i32;
  IntArrayPtr = ^IntArray;

procedure sort(list_ptr: IntArrayPtr);
var
  len, i, j: u32;
  tmp: i32;
begin
  len := length(list_ptr^);
  if len <= 1 then begin
    exit()
  end;
  for i := 0 to len-2 do begin
    for j := i+1 to len-1 do begin
      if list_ptr^[i] > list_ptr^[j] then begin
        tmp := list_ptr^[i];
        list_ptr^[i] := list_ptr^[j];
        list_ptr^[j] := tmp
      end
    end
  end
end;

//
// Main
//
var
  count, i: u32;
  sum: u32 = 0;
  list_a, list_b: Array of i32;
begin
  readln(count);
  setlength(list_a, count);
  setlength(list_b, count);

  for i := 0 to count-1 do read(list_a[i]);
  for i := 0 to count-1 do read(list_b[i]);

  // list_a 오름차순으로 정렬
  sort(@list_a);

  // list_b 내림차순으로 정렬
  for i := 0 to count-1 do list_b[i] := -list_b[i];
  sort(@list_b);
  for i := 0 to count-1 do list_b[i] := -list_b[i];

  // NOTE: Uncomment these lines to debug something
  //write('[');for i := 0 to count-1 do write(list_a[i], ' ');write(#8']'#10);
  //write('[');for i := 0 to count-1 do write(list_b[i], ' ');write(#8']'#10);

  // 출력
  for i := 0 to count-1 do sum := sum + list_a[i]*list_b[i];
  writeln(sum);
end.
