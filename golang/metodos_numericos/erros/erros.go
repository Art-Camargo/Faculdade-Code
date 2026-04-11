package merrors

import (
	"fmt"
	"math"
	"os"
	"strings"
)

func createCsvAndWriteHeader(fileName string) {
	f, err := os.Create(fileName)
	if err != nil {
		fmt.Println("Error creating file:", err)
		return
	}
	defer f.Close()
	header := "Termos da série;Estimativa de e^x;et(x);ea(x)\n"
	if _, err := f.WriteString(header); err != nil {
		fmt.Println("Error writing to file:", err)
	}
}

func appendCsv(fileName, data string) {
	f, err := os.OpenFile(fileName, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer f.Close()

	if _, err := f.WriteString(data); err != nil {
		fmt.Println("Error writing to file:", err)
	}
}

func AbsPercentage(main, diff float64) float64 {
	return math.Abs((main - diff) / main) * 100
}

func TaylorSerie(valorReal, tolerancia float64) {
	prev := float64(0)
	curr := float64(1)
	filename := "erros.csv"
	serieTerms := []string{"1"}
	createCsvAndWriteHeader(filename)

	for i := 0; ; i++ {
		currErrorPercentage := float64(0)
		currToleranciaPercentage := float64(0)
		if i == 0 {
			currErrorPercentage = AbsPercentage(valorReal, curr) 
			prev = curr
			data := fmt.Sprintf("1;%.6f;%.6f;%.6f\n", curr, currErrorPercentage, currToleranciaPercentage)
			appendCsv(filename, data)
			continue
		}

		curr = prev + (math.Pow(3, float64(i)) / math.Gamma(float64(i + 1)))
    currErrorPercentage = AbsPercentage(valorReal, curr)
		currToleranciaPercentage = AbsPercentage(curr, prev)
		currentTerm := fmt.Sprintf("X^%d/%d!", i, i)
		serieTerms = append(serieTerms, currentTerm)
		terms := strings.Join(serieTerms, " + ")
		if (math.Abs(currToleranciaPercentage) < tolerancia) {
			data := fmt.Sprintf("%s;%.6f;%.6f;%.6f\n",terms,  curr, currErrorPercentage, currToleranciaPercentage)
			appendCsv(filename, data)
			break
		}
		prev = curr
		data := fmt.Sprintf("%s;%.6f;%.6f;%.6f\n", terms, curr, currErrorPercentage, currToleranciaPercentage)
		appendCsv(filename, data)
	}
}