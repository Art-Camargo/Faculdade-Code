package main

import (
	"math"
	merrors "metodos_numericos/erros"
)

func main() {
	valorReal := math.Pow(math.E, 3)
	tolerancia := 0.001

	merrors.TaylorSerie(valorReal, tolerancia)
}