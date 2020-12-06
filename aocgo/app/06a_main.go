package main

import (
	"log"
	"time"

	"github.com/obiwahn/advent_of_code/aocgo/pkg/extio"
)

func main() {
	start := time.Now()

	result := 0
	set := make(map[rune]int)

	extio.ForInputLine(func(line string) {
		if line == "" {
			//count reset
			for _, value := range set {
				result += value
			}
			set = make(map[rune]int)
		} else {
			for _, value := range line {
				set[value] = 1
			}
		}
	})

	end := time.Now()
	log.Printf("total time %s", end.Sub(start))

	log.Printf("the restult is: %v", result)
}
