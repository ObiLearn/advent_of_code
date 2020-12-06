package main

import (
	"fmt"
	"log"
	"sync"
	"time"

	"github.com/obiwahn/advent_of_code/aocgo/pkg/extio"
)

func solveInstance(lines []string, instanceResults chan<- int, wg *sync.WaitGroup) {
	defer wg.Done()
	set := make(map[rune]int)

	for _, line := range lines {
		for _, value := range line {
			set[value] = 1
		}
	}

	result := 0
	for _, value := range set {
		result += value
	}

	instanceResults <- result
}

func main() {
	start := time.Now()

	intermediateResults := make(chan int, 1000)

	lines, errs := extio.InputLines()

	var wg sync.WaitGroup
	data := []string{}
	for line := range lines {
		if line == "" {
			wg.Add(1)
			go solveInstance(data, intermediateResults, &wg)
			data = []string{}
		} else {
			data = append(data, line)
		}
	}

	if err := <-errs; err != nil {
		log.Fatalf("Error when reading input: %v", err)
	}

	wg.Wait()
	close(intermediateResults)

	result := 0
	for value := range intermediateResults {
		fmt.Println(value)
		result += value
	}

	end := time.Now()
	log.Printf("total time %s", end.Sub(start))

	log.Printf("the restult is: %v", result)
}
