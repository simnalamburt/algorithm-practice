BASE_CASES = [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233]

# fibo2(num) 은 num번째와 num+1 번째 피보나치 수를 반환하는 함수다
def fibo2(num)
  # Base cases
  return [BASE_CASES[num], BASE_CASES[num+1]] if num < 13

  # d'Ocagne's identity
  # Reference: https://en.wikipedia.org/wiki/Fibonacci_number#d'Ocagne's_identity
  k = num / 2
  fibo_k0, fibo_k1 = fibo2(k)
  return (
      num % 2 == 0 ?
      [fibo_k0*(2*fibo_k1 - fibo_k0), fibo_k0**2 + fibo_k1**2] :
      [fibo_k0**2 + fibo_k1**2, fibo_k1*(2*fibo_k0 + fibo_k1)]
  )
end

num = gets.to_i
answer = fibo2(num)[0]
puts(answer)
