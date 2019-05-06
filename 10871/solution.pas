var
  count, value_x, value: Word;
  is_first: Boolean = true;
begin
  read(count, value_x);
  while count > 0 do begin
    read(value);
    if value < value_x then begin
      if not is_first then write(' ')
      else is_first := false;
      write(value)
    end;
    dec(count)
  end
end.
