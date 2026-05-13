import math

def f(x):
    return 0.2 + 25*x - 200*x**2 + 675*x**3 - 900*x**4 + 400*x**5

def F(x):
    """
    Integral exata de f(x):
    ∫f(x)dx = 0.2x + 25x²/2 - 200x³/3 + 675x⁴/4 - 900x⁵/5 + 400x⁶/6
    """
    return (
        0.2*x
        + (25*x**2)/2
        - (200*x**3)/3
        + (675*x**4)/4
        - (900*x**5)/5
        + (400*x**6)/6
    )

def f_prime(x):
    return 25 - 400*x + 2025*x**2 - 3600*x**3 + 2000*x**4

def f_second(x):
    return -400 + 4050*x - 10800*x**2 + 8000*x**3

def max_abs_f_second(a, b):
    """
    Como f''(x) é cúbica, o máximo absoluto em [a,b]
    pode estar nos extremos ou onde f'''(x)=0.

    f'''(x) = 4050 - 21600x + 24000x²
    """
    candidates = [a, b]

    A = 24000
    B = -21600
    C = 4050

    delta = B**2 - 4*A*C

    if delta >= 0:
        x1 = (-B + math.sqrt(delta)) / (2*A)
        x2 = (-B - math.sqrt(delta)) / (2*A)

        if a <= x1 <= b:
            candidates.append(x1)

        if a <= x2 <= b:
            candidates.append(x2)

    return max(abs(f_second(x)) for x in candidates)

def trapezio(n, a=0, b=0.8):
    h = (b - a) / n

    valor_verdadeiro = F(b) - F(a)

    soma = f(a) + f(b)

    for i in range(1, n):
        x_i = a + i*h
        soma += 2 * f(x_i)

    aproximacao = (h / 2) * soma

    erro_verdadeiro = valor_verdadeiro - aproximacao

    erro_percentual = abs(erro_verdadeiro / valor_verdadeiro) * 100

    max_f2 = max_abs_f_second(a, b)

    erro_aprox_max_abs = ((b - a) / 12) * (h**2) * max_f2

    media_f2 = (f_prime(b) - f_prime(a)) / (b - a)

    erro_aprox_media = -((b - a) / 12) * (h**2) * media_f2

    return {
        "a": a,
        "b": b,
        "n": n,
        "h": h,
        "valor verdadeiro": valor_verdadeiro,
        "aproximação": aproximacao,
        "Et": erro_verdadeiro,
        "εt (%)": erro_percentual,
        "Ea máximo absoluto de f''(x)": erro_aprox_max_abs,
        "Ea média de f''(x)": erro_aprox_media,
    }

def imprimir_tabela(resultado):
    print()
    print(f"Tabela da regra do trapézio com n = {resultado['n']}")
    print("-" * 120)

    headers = [
        "a",
        "b",
        "h",
        "valor verdadeiro",
        "aproximação",
        "Et",
        "εt (%)",
        "Ea máx abs f''(x)",
        "Ea média f''(x)",
    ]

    values = [
        resultado["a"],
        resultado["b"],
        resultado["h"],
        resultado["valor verdadeiro"],
        resultado["aproximação"],
        resultado["Et"],
        resultado["εt (%)"],
        resultado["Ea máximo absoluto de f''(x)"],
        resultado["Ea média de f''(x)"],
    ]

    for h in headers:
        print(f"{h:<24}", end="")
    print()

    for v in values:
        if isinstance(v, float):
            print(f"{v:<24.10f}", end="")
        else:
            print(f"{v:<24}", end="")
    print()
    print("-" * 120)

if __name__ == "__main__":
    n = int(input("Digite o valor de n: "))

    resultado = trapezio(n)
    imprimir_tabela(resultado)