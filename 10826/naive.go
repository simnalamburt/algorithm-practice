package main

import (
	"fmt"
	"math/big"
)

func main() {
	var num int
	fmt.Scanf("%d", &num)

	var a, b, tmp big.Int
	b.SetInt64(1)
	for num > 0 {
		tmp.Add(&a, &b)
		a.Set(&b)
		b.Set(&tmp)
		num -= 1
	}
	fmt.Println(a.String())
}
