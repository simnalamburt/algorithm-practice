// fpc solution.pas -O2 -Coti -vwnh
//
// Reference: https://www.acmicpc.net/problem/2749

// Pisano period
// Reference: https://en.wikipedia.org/wiki/Pisano_period
const
  MODULO: Int64 = 1000000;
  PISANO_PERIOD: Int64 = 1500000;
  BASE_CASES: Packed Array [0..13] of Byte = (
    0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233
  );

type
  Pair = record
    _0: Int64;
    _1: Int64;
  end;

// fibo2(num) 은 num번째와 num+1 번째 피보나치 수를 반환하는 함수다
function fibo2(num: Int64): Pair;
var
  k: Int64;
  fibo_k: Pair;
begin
  // Base cases
  if num < 13 then begin
    fibo2._0 := BASE_CASES[num];
    fibo2._1 := BASE_CASES[num + 1];
    exit(fibo2)
  end;

  // d'Ocagne's identity
  // Reference: https://en.wikipedia.org/wiki/Fibonacci_number#d'Ocagne's_identity
  k := num div 2;
  fibo_k := fibo2(k);
  if num mod 2 = 0 then begin
    fibo2._0 := fibo_k._0*(2*fibo_k._1 - fibo_k._0);
    fibo2._1 := fibo_k._0*fibo_k._0 + fibo_k._1*fibo_k._1
  end else begin
    fibo2._0 := fibo_k._0*fibo_k._0 + fibo_k._1*fibo_k._1;
    fibo2._1 := fibo_k._1*(2*fibo_k._0 + fibo_k._1)
  end;

  // Mod out
  fibo2._0 := fibo2._0 mod MODULO;
  fibo2._1 := fibo2._1 mod MODULO;
  if fibo2._0 < 0 then
    fibo2._0 += MODULO;
  if fibo2._1 < 0 then
    fibo2._1 += MODULO;
end;

var
  num: Int64;
begin
  readln(num);
  writeln(fibo2(num mod PISANO_PERIOD)._0)
end.
