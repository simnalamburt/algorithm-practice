// fpc solution.pas -O2 -Coti -vwnh
//
// Reference: https://www.acmicpc.net/problem/2749

// Pisano period
// Reference: https://en.wikipedia.org/wiki/Pisano_period
const
  MODULO: Int64 = 1000000;
  PISANO_PERIOD: Int64 = 1500000;
  BASE_CASES: Array [0..13] of Byte = (
    0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233
  );

function fibo(num: Int64): Int64;
var
  k: Int64;
  fibo_k0: Int64;
  fibo_k1: Int64;
begin
  // Base cases
  if num < 14 then
    exit(BASE_CASES[num]);

  // d'Ocagne's identity
  // Reference: https://en.wikipedia.org/wiki/Fibonacci_number#d'Ocagne's_identity
  k := num div 2;
  fibo_k0 := fibo(k);
  fibo_k1 := fibo(k + 1);
  if num mod 2 = 0 then
    fibo := fibo_k0*(2*fibo_k1 - fibo_k0)
  else
    fibo := fibo_k1*fibo_k1 + fibo_k0*fibo_k0;
  fibo := fibo mod MODULO;
  if fibo < 0 then
    fibo := fibo + MODULO
end;

var
  num: Int64;
begin
  readln(num);
  writeln(fibo(num mod PISANO_PERIOD))
end.
