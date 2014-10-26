package main

import "fmt"

type lambda_t struct {
	n int
}

func (lambda *lambda_t) call(i int) int {
	lambda.n += i
	return lambda.n
}

func foo(n int) *lambda_t {
	return &lambda_t{n}
}

func main() {
	lambda := foo(0)
	fmt.Println(lambda.call(1))
	fmt.Println(lambda.call(1))
}
