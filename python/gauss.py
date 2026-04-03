import copy

EPS = 1e-12

def print_matrix(mat):
    for row in mat:
        print(["{:.2f}".format(x) for x in row])
    print()


def print_etapa(titulo, mat):
    print(titulo)
    print_matrix(mat)


def validar_matriz_aumentada(mat):
    if not mat or not isinstance(mat, list):
        raise ValueError("Matriz inválida.")

    n = len(mat)
    expected_cols = n + 1
    for row in mat:
        if len(row) != expected_cols:
            raise ValueError(
                f"Matriz aumentada inválida: esperado {expected_cols} valores por linha para {n} equações."
            )


def escolher_pivo(mat, i):
    n = len(mat)
    pivot_row = i
    max_abs = abs(mat[i][i])

    for r in range(i + 1, n):
        current = abs(mat[r][i])
        if current > max_abs:
            max_abs = current
            pivot_row = r

    return pivot_row, max_abs


def gauss(mat):
    mat = copy.deepcopy(mat)
    validar_matriz_aumentada(mat)
    n = len(mat)

    print_etapa("Matriz inicial:", mat)

    # Eliminação
    for i in range(n):
        # Pivotamento parcial
        pivot_row, pivot_val = escolher_pivo(mat, i)
        if pivot_val < EPS:
            raise ValueError("Sistema sem solução única (matriz singular ou indeterminada).")
        if pivot_row != i:
            mat[i], mat[pivot_row] = mat[pivot_row], mat[i]
            print_etapa(f"Troca de linhas L{i+1} <-> L{pivot_row+1}:", mat)

        # Zerar abaixo
        for j in range(i + 1, n):
            fator = mat[j][i] / mat[i][i]
            for k in range(len(mat[0])):
                mat[j][k] -= fator * mat[i][k]
            print_etapa(f"L{j+1} = L{j+1} - ({fator:.4f}) * L{i+1}:", mat)

    print("Matriz triangular:")
    print_matrix(mat)

    # Substituição regressiva
    x = [0] * n
    for i in range(n - 1, -1, -1):
        soma = mat[i][-1]
        for j in range(i + 1, n):
            soma -= mat[i][j] * x[j]
        if abs(mat[i][i]) < EPS:
            raise ValueError("Sistema sem solução única (matriz singular ou indeterminada).")
        x[i] = soma / mat[i][i]

    return x


def gauss_jordan(mat):
    mat = copy.deepcopy(mat)
    validar_matriz_aumentada(mat)
    n = len(mat)

    print_etapa("Matriz inicial:", mat)

    for i in range(n):
        # Pivotamento parcial
        pivot_row, pivot_val = escolher_pivo(mat, i)
        if pivot_val < EPS:
            raise ValueError("Sistema sem solução única (matriz singular ou indeterminada).")
        if pivot_row != i:
            mat[i], mat[pivot_row] = mat[pivot_row], mat[i]
            print_etapa(f"Troca de linhas L{i+1} <-> L{pivot_row+1}:", mat)

        # Normalizar linha
        piv = mat[i][i]
        for j in range(len(mat[0])):
            mat[i][j] /= piv
        print_etapa(f"Normalização da linha L{i+1}:", mat)

        # Zerar outras linhas
        for k in range(n):
            if k != i:
                fator = mat[k][i]
                for j in range(len(mat[0])):
                    mat[k][j] -= fator * mat[i][j]
                print_etapa(f"L{k+1} = L{k+1} - ({fator:.4f}) * L{i+1}:", mat)

    print("Matriz reduzida:")
    print_matrix(mat)

    return [row[-1] for row in mat]


# Sistemas prontos: 3 das imagens + 5 extras (fora da lista)
sistemas = {
    1: [
        [1, 1, 2, 8],
        [-1, -2, 3, 1],
        [3, -7, 4, 10]
    ],
    2: [
        [1, -1, 2, -1, -1],
        [2, 1, -2, -2, -2],
        [-1, 2, -4, 1, 1],
        [3, 0, 0, -3, -3]
    ],
    3: [
        [3, 0, -2, 5],
        [7, 1, 4, -3],
        [0, -2, 1, 7]
    ],
    4: [
        [2, -1, 1, 8],
        [1, 3, 2, 13],
        [3, -2, -1, -1]
    ],
    5: [
        [4, 1, -2, 2],
        [3, -1, 1, 1],
        [1, 2, 3, 14]
    ],
    6: [
        [1, 2, 1, 9],
        [2, 1, -1, 8],
        [3, -1, 2, 10]
    ],
    7: [
        [1, 1, 1, 1, 10],
        [2, -1, 3, 1, 5],
        [1, 3, -1, 2, 8],
        [3, 1, 2, -2, 7]
    ],
    8: [
        [2, 0, 1, -1, 1],
        [1, 1, 0, 2, 6],
        [3, -1, 2, 1, 8],
        [0, 2, -1, 1, 2]
    ]
}


def input_matrix():
    n = int(input("Número de equações: "))
    mat = []
    print("Digite a matriz aumentada linha por linha:")
    for i in range(n):
        row = list(map(float, input().split()))
        mat.append(row)
    return mat


def main():
    print("1 - Usar sistema pronto")
    print("2 - Inserir sistema manual")
    escolha = int(input("Escolha: "))

    if escolha == 1:
        print("Sistemas prontos:")
        print("1 - Imagem (a): sistema 3x3")
        print("2 - Imagem (b): sistema 4x4")
        print("3 - Imagem 2: matriz aumentada 3x3")
        print("4 - Extra 1")
        print("5 - Extra 2")
        print("6 - Extra 3")
        print("7 - Extra 4")
        print("8 - Extra 5")
        s = int(input())
        if s not in sistemas:
            raise ValueError("Sistema inválido. Escolha entre 1 e 8.")
        mat = sistemas[s]
    else:
        mat = input_matrix()

    print("1 - Gauss")
    print("2 - Gauss-Jordan")
    metodo = int(input("Método: "))

    try:
        if metodo == 1:
            sol = gauss(mat)
        elif metodo == 2:
            sol = gauss_jordan(mat)
        else:
            raise ValueError("Método inválido. Escolha 1 ou 2.")
    except ValueError as e:
        print(f"Erro: {e}")
        return

    print("Solução:")
    for i, val in enumerate(sol):
        print(f"x{i+1} = {val:.2f}")


if __name__ == "__main__":
    main()