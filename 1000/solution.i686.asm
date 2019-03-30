section .data
  input: db "%d %d",0
  output: db "%d",10,0
  a: times 4 db 0
  b: times 4 db 0

section .text
  global main
  extern scanf
  extern printf

main:
  ; prologue
  push ebx
  push ecx

  ; call scanf
  push b
  push a
  push input
  call scanf
  add esp, 12

  ; a + b
  mov ebx, dword[a]
  mov ecx, dword[b]
  add ebx, ecx

  ; call printf
  push ebx
  push output
  call printf
  add esp, 8

  ; epilogue, return 0
  pop ecx
  pop ebx
  mov eax,0
  ret
