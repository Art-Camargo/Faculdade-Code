def f(x):
    return -2*x**3 + 12*x**2 - 20*x + 8.5

def y_exato(x):
    return -0.5*x**4 + 4*x**3 - 10*x**2 + 8.5*x + 1

a = 0.0
b = 4.0
h = 0.5
y = 1.0
x = a

print("Método de Euler com erro verdadeiro e erro percentual")
print("y' = -2x³ + 12x² - 20x + 8.5")
print("y(0) = 1")
print(f"Intervalo: [{a}, {b}]")
print(f"h = {h}")
print()

print(
    f"{'i':>2} | "
    f"{'x_i':>6} | "
    f"{'y_i Euler':>12} | "
    f"{'f(x_i)':>10} | "
    f"{'h*f(x_i)':>12} | "
    f"{'x_(i+1)':>8} | "
    f"{'y_(i+1) Euler':>16} | "
    f"{'y exato':>10} | "
    f"{'Et':>10} | "
    f"{'εt (%)':>10}"
)
print("-" * 125)

i = 0

while x < b:
    fx = f(x)
    incremento = h * fx

    x_proximo = x + h
    y_proximo = y + incremento

    y_real = y_exato(x_proximo)

    Et = y_real - y_proximo
    et_percentual = abs(Et / y_real) * 100

    print(
        f"{i:>2} | "
        f"{x:>6.2f} | "
        f"{y:>12.5f} | "
        f"{fx:>10.5f} | "
        f"{incremento:>12.5f} | "
        f"{x_proximo:>8.2f} | "
        f"{y_proximo:>16.5f} | "
        f"{y_real:>10.5f} | "
        f"{Et:>10.5f} | "
        f"{et_percentual:>10.2f}"
    )

    x = x_proximo
    y = y_proximo
    i += 1

print()
print(f"Resultado pelo método de Euler: y({b:.0f}) ≈ {y:.5f}")
print(f"Valor exato: y({b:.0f}) = {y_exato(b):.5f}")
print(f"Erro verdadeiro final: {y_exato(b) - y:.5f}")
print(f"Erro percentual final: {abs((y_exato(b) - y) / y_exato(b)) * 100:.2f}%")