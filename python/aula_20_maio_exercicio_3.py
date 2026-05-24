import math

def f(x):
    return math.sqrt(x)

def f2(x):
    return -1 / (4 * x ** 1.5)

def trapezio_multiplo(a, b, n):
    h = (b - a) / n

    soma = f(a) + f(b)

    for i in range(1, n):
        x = a + i * h
        soma += 2 * f(x)

    return (h / 2) * soma

def media_f2(a, b):
    # media de f'' no intervalo = integral de f'' / (b-a)
    # f'(x) = 1 / (2sqrt(x))
    fp_b = 1 / (2 * math.sqrt(b))
    fp_a = 1 / (2 * math.sqrt(a))

    return (fp_b - fp_a) / (b - a)

a = 1
b = 4
valor_verdadeiro = 14 / 3

print("EXERCÍCIO 3 - TRAPÉZIO")
print()

print("n | h | aproximação | Et | εt(%) | Ea máx abs f'' | Ea média f''")

for n in range(1, 7):
    h = (b - a) / n
    aproximacao = trapezio_multiplo(a, b, n)

    Et = valor_verdadeiro - aproximacao
    et_percentual = abs(Et / valor_verdadeiro) * 100

    max_abs_f2 = abs(f2(a))
    media = media_f2(a, b)

    Ea_max = ((b - a) * h ** 2 / 12) * max_abs_f2
    Ea_media = -((b - a) * h ** 2 / 12) * media

    print(
        n,
        "|",
        round(h, 6),
        "|",
        round(aproximacao, 6),
        "|",
        round(Et, 6),
        "|",
        round(et_percentual, 6),
        "|",
        round(Ea_max, 6),
        "|",
        round(Ea_media, 6)
    )