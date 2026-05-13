def f(x):
    return 0.2 + 25*x - 200*x**2 + 675*x**3 - 900*x**4 + 400*x**5


def F(x):
    # Primitiva de f(x)
    return (
        0.2*x
        + (25*x**2)/2
        - (200*x**3)/3
        + (675*x**4)/4
        - (900*x**5)/5
        + (400*x**6)/6
    )


def f_prime(x):
    # Primeira derivada de f(x)
    return 25 - 400*x + 2025*x**2 - 3600*x**3 + 2000*x**4


def trapezio_composto(n, a=0, b=0.8):
    h = (b - a) / n

    valor_verdadeiro = F(b) - F(a)

    soma = f(a) + f(b)

    for i in range(1, n):
        x_i = a + i * h
        soma += 2 * f(x_i)

    aproximacao = (h / 2) * soma

    Et = valor_verdadeiro - aproximacao

    erro_percentual = abs(Et / valor_verdadeiro) * 100

    # Conforme usado no exemplo:
    # max |f''(x)| = 400
    max_abs_f2 = 400

    Ea_max_abs = ((b - a) / 12) * (h**2) * max_abs_f2

    # média de f''(x) = [f'(b) - f'(a)] / (b-a)
    media_f2 = (f_prime(b) - f_prime(a)) / (b - a)

    Ea_media = -((b - a) / 12) * (h**2) * media_f2

    return {
        "n": n,
        "h": h,
        "aproximacao": aproximacao,
        "Et": Et,
        "erro_percentual": erro_percentual,
        "Ea_max_abs": Ea_max_abs,
        "Ea_media": Ea_media,
    }


def imprimir_tabela(n_inicial=3, n_final=10):
    print("Tabela da aplicação múltipla da regra do trapézio")
    print(f"n de {n_inicial} a {n_final}")
    print()

    print(
        f"{'n':<5}"
        f"{'h':<18}"
        f"{'aproximação':<18}"
        f"{'Et':<18}"
        f"{'εt (%)':<18}"
        f"{'Ea máx abs f2':<22}"
        f"{'Ea média f2':<18}"
    )

    print("-" * 117)

    for n in range(n_inicial, n_final + 1):
        r = trapezio_composto(n)

        print(
            f"{r['n']:<5}"
            f"{r['h']:<18.10f}"
            f"{r['aproximacao']:<18.10f}"
            f"{r['Et']:<18.10f}"
            f"{r['erro_percentual']:<18.10f}"
            f"{r['Ea_max_abs']:<22.10f}"
            f"{r['Ea_media']:<18.10f}"
        )


if __name__ == "__main__":
    imprimir_tabela(3, 10)