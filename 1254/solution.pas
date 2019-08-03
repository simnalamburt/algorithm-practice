// fpc solution.pas -O2 -Coti -vwnh

function is_palindrome(str: String): Boolean;
var
  len, i: Int64;
begin
  len := length(str);
  for i := 1 to len div 2 do begin
    if str[i] <> str[len - i + 1] then begin
      exit(false)
    end
  end;
  is_palindrome := true
end;

var
  str, substr: String;
  len, min, i: Int64;
begin
  read(str);
  len := length(str);

  min := len - 1;
  for i := 1 to len - 1 do begin
    substr := copy(str, i, len - i + 1);
    if is_palindrome(substr) then begin
      min := i - 1;
      break
    end
  end;

  writeln(min + len)
end.
