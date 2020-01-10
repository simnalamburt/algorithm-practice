const fs = require('fs')

const input = fs.readFileSync('/dev/stdin')
const [a, b] = input.toString().split(' ')
console.log((a | 0) + (b | 0))
