// fpc assembly.pas -O2 -Co -Ct -Ci

// I like inline assembly
//
// Reference:
//   http://wiki.freepascal.org/Asm
//   https://www.freepascal.org/docs-html/prog/progsu111.html#x119-1200001.3.28
//   https://www.freepascal.org/docs-html/prog/progsu58.html#x65-640001.2.58
{$asmMode intel}
{$PIC OFF}
{$INLINE ON}

type
  i64 = Int64;

var
  a, b: i64;
begin
  read(a, b);
  asm
    mov rax, [a]
    mov rbx, [b]
    add rax, rbx
    mov [a], rax
  end ['rax', 'rbx'];
  writeln(a)
end.
