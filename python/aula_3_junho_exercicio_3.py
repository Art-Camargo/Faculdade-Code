import math

h = 1
a = 0
b = 4

x = a
y = 2

def f(x, y):
    return 4 * math.exp(0.8 * x) - 0.5 * y

def y_verdadeiro(x):
    return (40 / 13) * math.exp(0.8 * x) - (14 / 13) * math.exp(-0.5 * x)

n = 0

print("n | x_n | y_n | f(x_n,y_n) | x_n+1 | y0_n+1 | f(x_n+1,y0_n+1) | y_n+1 | y_v | E_T | Et(%)")

while x < b:
    f_inicial = f(x, y)

    x_proximo = x + h

    # previsão de Euler
    y_previsao = y + h * f_inicial

    # inclinação no ponto previsto
    f_previsto = f(x_proximo, y_previsao)

    # correção de Heun
    y_proximo = y + (h / 2) * (f_inicial + f_previsto)

    yv = y_verdadeiro(x_proximo)

    erro_verdadeiro = yv - y_proximo
    et_percentual = (erro_verdadeiro / yv) * 100

    print(
        n, "|",
        round(x, 6), "|",
        round(y, 6), "|",
        round(f_inicial, 6), "|",
        round(x_proximo, 6), "|",
        round(y_previsao, 6), "|",
        round(f_previsto, 6), "|",
        round(y_proximo, 6), "|",
        round(yv, 6), "|",
        round(erro_verdadeiro, 6), "|",
        str(round(et_percentual, 2)) + "%"
    )

    x = x_proximo
    y = y_proximo
    n += 1