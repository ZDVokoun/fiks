package main

import (
	"fmt"
)

type QueueItem struct {
	m      [][]int
	sym    string
	result [][]bool
}

type Position struct {
	x int
	y int
}

func print2d(m [][]int) {
	for _, line := range m {
		fmt.Println(line)
	}
	fmt.Println("")
}

func min(a int, b int) int {
	if a < b {
		return a
	} else {
		return b
	}
}

func copy2D(m *[][]int, a *[][]int, n int) {
	*a = make([][]int, n)
	for i := 0; i < n; i++ {
		line := make([]int, n)
		for j := 0; j < n; j++ {
			line[j] = (*m)[i][j]
		}
		(*a)[i] = line
	}
}

func copy2DBool(m *[][]bool, a *[][]bool, n int) {
	*a = make([][]bool, n)
	for i := 0; i < n; i++ {
		line := make([]bool, n)
		for j := 0; j < n; j++ {
			line[j] = (*m)[i][j]
		}
		(*a)[i] = line
	}
}

func numberOfChanged(m [][]bool) int {
	result := 0
	for _, line := range m {
		for _, item := range line {
			if item {
				result++
			}
		}
	}
	return result
}

func in(n int, arr []int) bool {
	for _, i := range arr {
		if n == i {
			return true
		}
	}
	return false
}

func getOpened(m [][]bool) (Position, bool) {
	for y, line := range m {
		for x, cell := range line {
			if cell == false {
				return Position{x, y}, true
			}
		}
	}
	return Position{-1, -1}, false
}

func task(before [][]int, sym string, n int) int {
	m := make([][]int, n)
	copy2D(&before, &m, n)
	closed := make([][]bool, n)
	for i := 0; i < n; i++ {
		closed[i] = make([]bool, n)
	}
	queue := make([]Position, 0)
	for next, run := getOpened(closed); run; next, run = getOpened(closed) {
		queue = append(queue, next)
		toCheck := []Position{next}
		closed[next.y][next.x] = true
		for len(queue) > 0 {
			current := queue[0]
			queue = queue[1:]

			x := current.x
			y := current.y

			for _, ch := range sym {
				switch ch {
				case '|':
					if !closed[y][n-x-1] {
						queue = append(queue, Position{n - x - 1, y})
						toCheck = append(toCheck, Position{n - x - 1, y})
						closed[y][n-x-1] = true
					}

				case '-':
					if !closed[n-1-y][x] {
						queue = append(queue, Position{x, n - 1 - y})
						toCheck = append(toCheck, Position{x, n - 1 - y})
						closed[n-y-1][x] = true
					}

				case '/':
					if !closed[n-x-1][n-y-1] {
						queue = append(queue, Position{n - 1 - y, n - 1 - x})
						toCheck = append(toCheck, Position{n - 1 - y, n - 1 - x})
						closed[n-x-1][n-y-1] = true
					}

				case '\\':
					if !closed[x][y] {
						queue = append(queue, Position{y, x})
						toCheck = append(toCheck, Position{y, x})
						closed[x][y] = true
					}
				}
			}
		}
		occurency := make(map[int][]Position, n)
		var positions []Position
		var positionsValue int
		for _, i := range []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9} {
			occurency[i] = make([]Position, 0)
		}
		for _, pos := range toCheck {
			occurency[m[pos.y][pos.x]] = append(occurency[m[pos.y][pos.x]], pos)
		}
		for k, v := range occurency {
			if len(v) > len(positions) || (len(v) == len(positions) && k < positionsValue) {
				positions = v
				positionsValue = k
			}
		}
		for _, v := range occurency {
			for _, pos := range v {
				x := pos.x
				y := pos.y
				m[y][x] = positionsValue
			}
		}
	}

	result := 0
	for y := 0; y < n; y++ {
		for x := 0; x < n; x++ {
			if m[y][x] != before[y][x] {
				result++
			}
		}
	}
	return result
}

func main() {
	var t int
	fmt.Scanf("%d", &t)
	for i := 0; i < t; i++ {
		var s int
		var sym string
		var n int
		fmt.Scanf("%d", &s)
		fmt.Scanf("%s", &sym)
		fmt.Scanf("%d", &n)

		a := make([][]int, n)
		for j := 0; j < n; j++ {
			line := make([]int, n)
			for k := 0; k < n; k++ {
				var cell int
				fmt.Scanf("%d", &cell)
				line[k] = cell
			}
			fmt.Scanf(" \n")
			a[j] = line
		}
		fmt.Printf("%d\n", task(a, sym, n))
	}
}
