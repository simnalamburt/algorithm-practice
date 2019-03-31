package main

import "fmt"

const data = `Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec quis lectus sit amet ante suscipit tempor. Aenean dapibus finibus tortor vitae facilisis. Nulla facilisi. Donec suscipit ante a sapien gravida eleifend. Curabitur in lectus ut enim semper venenatis. Aenean elit nibh, hendrerit nec nunc in, dictum cursus dolor. Aenean eget lectus risus. Cras sollicitudin quam vitae augue mollis bibendum. Aliquam euismod vulputate dolor at tristique. Praesent elementum pretium velit non interdum. Nunc posuere faucibus magna id pretium. Maecenas congue, velit eget semper porttitor, tellus tortor porttitor dui, tristique lobortis quam sem ac odio.`

func main() {
	var a, b int
	fmt.Scanf("%d%d", &a, &b)
	a -= 1

	count := 0
	begin := 0
	end := len(data)

	for pos, char := range data {
		if char != ' ' { continue }

		count += 1
		if count == a { begin = pos + 1 }
		if count == b { end = pos }
	}

	fmt.Println(data[begin:end])
}
