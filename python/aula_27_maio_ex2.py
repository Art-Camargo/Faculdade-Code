import math

h = 0.25
a = 0
b = 1

x = a
y = 2

def f(x, y):
    return y - x

def y_verdadeiro(x):
    return math.exp(x) + x + 1

n = 0

print("n | x | y_euler | y_verdadeiro | Et | Et(%)")

# imprime o ponto inicial
yv = y_verdadeiro(x)
et = yv - y
et_percentual = (et / yv) * 100

print(
    n, "|",
    round(x, 5), "|",
    round(y, 5), "|",
    round(yv, 5), "|",
    round(et, 5), "|",
    str(round(et_percentual, 2)) + "%"
)

while x < b:
    fx = f(x, y)

    x_proximo = x + h
    y_proximo = y + h * fx

    yv = y_verdadeiro(x_proximo)
    et = yv - y_proximo
    et_percentual = (et / yv) * 100

    n += 1

    print(
        n, "|",
        round(x_proximo, 5), "|",
        round(y_proximo, 5), "|",
        round(yv, 5), "|",
        round(et, 5), "|",
        str(round(et_percentual, 2)) + "%"
    )

    x = x_proximo
    y = y_proximo

# estimativa do erro de truncamento
max_segunda_derivada = math.exp(1)
erro_truncamento = (h**2 / 2) * max_segunda_derivada

print()
print("Estimativa do erro de truncamento:")
print("Ea <=", round(erro_truncamento, 5))