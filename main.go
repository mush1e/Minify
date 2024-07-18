package main

import "fmt"

func main() {
	intArr := [5]int32{}
	intArr[0] = 123
	fmt.Println(intArr[:])
	intSlice := []int32{1, 2}
	intSlice = append(intSlice, intArr[:]...)
	fmt.Println(intSlice)
}
