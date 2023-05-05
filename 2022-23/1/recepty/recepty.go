package main

import (
	"fmt"
	"sort"
)

type Needed struct {
	ingredience string
	number      int
}

type Recept struct {
	mades int
	needs []Needed
}

type Predmet struct {
	needed   int
	prebytek int
}

type Pair struct {
	key   string
	value int
}

func abs(a int) int {
	if a > 0 {
		return a
	} else {
		return -a
	}
}

func task(r map[string]Recept, p map[string]Predmet) map[string]int {
	result := make(map[string]int)
	run := true
	for run {
		run = false
		for k, v := range p {
			if v.needed < 0 || v.prebytek < 0 {
				panic("Negative")
			}

			// Kontrola potreby delat a bezet
			if v.needed == 0 {
				continue
			} else {
				run = true
			}
			if recipe, ok := r[k]; ok {
				// Vytvoreni receptu
				if recipe.mades > v.needed {
					v.prebytek += recipe.mades - v.needed
					v.needed = 0
				} else {
					v.needed -= recipe.mades
				}
				// Pridavani ingredienci do seznamu
				for _, ingredience := range recipe.needs {
					if item, ok := p[ingredience.ingredience]; ok {
						// Kontrola prebytku
						if item.prebytek > ingredience.number {
							item.prebytek -= ingredience.number
						} else {
							item.needed += ingredience.number - item.prebytek
							item.prebytek = 0
						}
						p[ingredience.ingredience] = item
					} else {
						p[ingredience.ingredience] = Predmet{ingredience.number, 0}
					}
				}
			} else {
				if _, ok := result[k]; ok {
					result[k] += v.needed + v.prebytek
				} else {
					result[k] = v.needed + v.prebytek
				}
				v.needed = 0
				v.prebytek = 0
			}

			// Asigning new value
			p[k] = v
		}
	}
	return result
}

func main() {
	var u int
	fmt.Scanf("%d\n", &u)
	// Zadani
	for u_i := 0; u_i < u; u_i++ {
		var r int
		fmt.Scanf("%d\n", &r)
		recipies := make(map[string]Recept)
		items := make(map[string]Predmet)
		// Recepty
		for i := 0; i < r; i++ {
			var r_i int
			fmt.Scanf("%d\n", &r_i)

			var mades int
			var recipeName string
			needs := make([]Needed, r_i)

			// Ingredience
			for j := 0; j < r_i; j++ {
				var name string
				var n int
				fmt.Scanf("%d %s", &n, &name)
				needs[j] = Needed{name, n}
			}
			fmt.Scanf("%d %s", &mades, &recipeName)
			recipies[recipeName] = Recept{mades, needs}
		}
		var p int
		fmt.Scanf("%d", &p)
		// Predmety
		for i := 0; i < p; i++ {
			var name string
			var n int
			fmt.Scanf("%d %s", &n, &name)
			items[name] = Predmet{n, 0}
		}

		result := task(recipies, items)
		fmt.Printf("%d\n", len(result))
		keys := make([]string, 0, len(result))
		for k := range result {
			keys = append(keys, k)
		}
		sort.Strings(keys)
		for _, k := range keys {
			fmt.Printf("%d %s\n", result[k], k)
		}

	}
}
