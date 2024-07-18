package main

import (
	"errors"
	"fmt"
)

func division(numerator, denominator int) (result, remainder int, err error) {
	if denominator == 0 {
		err = errors.New("Cannot divide by 0")
		return 0, 0, err
	}
	result = numerator / denominator
	remainder = numerator % denominator
	return
}

func main() {
	defer fmt.Println("Hello world!")
	result, remainder, err := division(12, 3)
	if err != nil {
		fmt.Println(err)
	} else if remainder == 0 {
		fmt.Println("Perfect division")
	} else {
		fmt.Println(result, remainder, err)
	}
}
