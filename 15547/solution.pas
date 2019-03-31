// fpc solution.pas -O2 -Coti -vwnh

// Use big string by default
{$H+}

const
  DATA: String = 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec quis lectus sit amet ante suscipit tempor. Aenean dapibus finibus tortor vitae facilisis. Nulla facilisi. Donec suscipit ante a sapien gravida eleifend. Curabitur in lectus ut enim semper venenatis. Aenean elit nibh, hendrerit nec nunc in, dictum cursus dolor. Aenean eget lectus risus. Cras sollicitudin quam vitae augue mollis bibendum. Aliquam euismod vulputate dolor at tristique. Praesent elementum pretium velit non interdum. Nunc posuere faucibus magna id pretium. Maecenas congue, velit eget semper porttitor, tellus tortor porttitor dui, tristique lobortis quam sem ac odio.';
var
  a, b, pos: Integer;
  count: Integer = 0;
  begin_at: Integer = 0;
  end_at: Integer = 647;
begin
  readln(a, b);
  a := a - 1;

  for pos := 1 to 646 do begin
    if DATA[pos] <> ' ' then continue;

    count := count + 1;
    if count = a then begin_at := pos + 1;
    if count = b then end_at := pos
  end;

  writeln(copy(DATA, begin_at, end_at - begin_at))
end.
