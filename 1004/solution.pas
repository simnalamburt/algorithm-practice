// fpc solution.pas -O2 -Coti -vwnh
type
  u8 = Byte;
  i16 = SmallInt;
  u32 = Cardinal;
var
  count, planet_count, sum: u8;
  src_x, src_y, dst_x, dst_y, planet_x, planet_y, src_dx, src_dy, dst_dx, dst_dy: i16;
  planet_r: u32;
begin
  read(count);
  while count > 0 do begin
    count := count - 1;
    read(src_x, src_y, dst_x, dst_y, planet_count);

    sum := 0;
    while planet_count > 0 do begin
      read(planet_x, planet_y, planet_r);

      src_dx := planet_x - src_x;
      src_dy := planet_y - src_y;
      dst_dx := planet_x - dst_x;
      dst_dy := planet_y - dst_y;
      planet_r := planet_r*planet_r;

      if (
        (src_dx*src_dx + src_dy*src_dy < planet_r) <>
        (dst_dx*dst_dx + dst_dy*dst_dy < planet_r)
      ) then sum := sum + 1;
      planet_count := planet_count - 1
    end;
    writeln(sum)
  end
end.
