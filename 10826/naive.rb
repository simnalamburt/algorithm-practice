num = gets.to_i
a = 0
b = 1
while num > 0 do
  tmp = a + b
  a, b = b, tmp
  num -= 1
end
puts a
