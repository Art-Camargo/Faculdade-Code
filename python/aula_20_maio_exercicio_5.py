import math

def f(x):
    return math.cos(x)

def f4(x):
    # A quarta derivada de cos(x) é cos(x)
    return math.cos(x)

def simpson_um_terco(a, b):
    h = (b - a) / 2
    x0 = a
    x1 = a + h
    x2 = b

    aproximacao = (h / 3) * (f(x0) + 4 * f(x1) + f(x2))

    return aproximacao

def media_f4(a, b):
    # media de f'''' no intervalo = integral de cos(x) / (b-a)
    # integral de cos(x) = sin(x)
    return (math.sin(b) - math.sin(a)) / (b - a)

a = 0.5
b = 1.5
valor_verdadeiro = 0.518069

h = (b - a) / 2
aproximacao = simpson_um_terco(a, b)

Et = valor_verdadeiro - aproximacao
et_percentual = abs(Et / valor_verdadeiro) * 100

# Em [0.5, 1.5], cos(x) é decrescente e positivo.
# Então o máximo absoluto de f'''' ocorre em x = 0.5.
max_abs_f4 = abs(f4(a))
media = media_f4(a, b)

Ea_max = -(((b - a) ** 5) / 2880) * max_abs_f4
Ea_media = -(((b - a) ** 5) / 2880) * media

print("EXERCÍCIO 5 - SIMPSON 1/3")
print()

print("a | b | h | valor verdadeiro | aproximação | Et | εt(%) | Ea máx abs f'''' | Ea média f''''")

print(
    round(a, 6),
    "|",
    round(b, 6),
    "|",
    round(h, 6),
    "|",
    round(valor_verdadeiro, 6),
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