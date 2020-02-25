package main

import (
	"fmt"
	"runtime"
)
// This is simple code in GOlang

/* Here we do sufff i like bois */
func main() {
	int a := 0
	"HELLO BOIS"
	10.00
	fmt.Print("Go runs on ")
	switch os := runtime.GOOS; os {
	a = 69;
	case "darwin":
		fmt.Println("OS X.")
	case "linux":
		fmt.Println("Linux.")
	default:
		// freebsd, openbsd,
		// plan9, windows...
		fmt.Printf("%s.\n", os)
	}
	a := 1000.0;
	float b := 10.55;
	float c := 0.555;
	int d := 69;
	int a := 55;
	string e :="Big bois";
}


package main

import (
	"fmt"
	"time"
)

func main() {
	t := time.Now()
	switch {
	case t.Hour() < 12:
		fmt.Println("Good morning!")
	case t.Hour() < 17:
		fmt.Println("Good afternoon.")
	default:
		fmt.Println("Good evening.")
	}
}



<END>
