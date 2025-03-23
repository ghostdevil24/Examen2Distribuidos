import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import linregress

# Leer el archivo CSV con los tiempos
df = pd.read_csv("tiempos.csv")

# Mostrar los datos
print("Datos leídos del archivo CSV:")
print(df)

# Combinaciones a analizar (en el orden especificado)
combinaciones = ["kij", "ikj", "ijk", "jik", "jki", "kji"]

# Colores para las gráficas
colores = {
    "kij": "blue",
    "ikj": "green",
    "ijk": "purple",
    "jik": "orange",
    "jki": "red",
    "kji": "brown"
}

# Función para graficar con escala logarítmica o lineal
def graficar_tiempos(tamaño, escala_log):
    # Filtrar los datos para el tamaño de matriz actual
    datos = df[df["tamaño"] == tamaño]
    
    plt.figure(figsize=(10, 6))
    for combinacion in combinaciones:
        # Graficar puntos de dispersión
        plt.scatter(combinacion, datos[combinacion].values[0], color=colores[combinacion], label=combinacion, s=100)
    
    # Calcular y dibujar la línea de tendencia
    x = np.arange(len(combinaciones))
    y = [datos[comb].values[0] for comb in combinaciones]
    slope, intercept, r_value, p_value, std_err = linregress(x, y)
    plt.plot(combinaciones, slope * x + intercept, color="black", linestyle="--", linewidth=2, label="Línea de tendencia")
    
    plt.title(f"Tiempos de ejecución para tamaño de matriz {tamaño}")
    plt.xlabel("Combinación de bucles")
    plt.ylabel("Tiempo (segundos)")
    
    if escala_log:
        plt.yscale("log")
        plt.grid(True, which="both", ls="--")
        plt.text(0.5, 0.1, "Escala logarítmica", transform=plt.gca().transAxes, fontsize=12, color="red")
    else:
        plt.grid(True, axis='y', ls="--")
    
    plt.legend()
    plt.savefig(f"tiempos_tamaño_{tamaño}.png")  # Guardar la gráfica en PNG
    plt.close()

# Gráficas para cada tamaño de matriz
tamanos = [10, 100, 500, 1000, 3000, 5000, 10000]
escalas_log = [True, True, True, False, False, False, False]  # Escala log para 10, 100, 500

for tamaño, escala_log in zip(tamanos, escalas_log):
    graficar_tiempos(tamaño, escala_log)

# Gráfica de dispersión de los tiempos promedios
promedios = df[combinaciones].mean()
plt.figure(figsize=(10, 6))
for combinacion in combinaciones:
    plt.scatter(combinacion, promedios[combinacion], color=colores[combinacion], label=combinacion, s=100)

# Línea de tendencia para los promedios
x = np.arange(len(combinaciones))
y = [promedios[comb] for comb in combinaciones]
slope, intercept, r_value, p_value, std_err = linregress(x, y)
plt.plot(combinaciones, slope * x + intercept, color="black", linestyle="--", linewidth=2, label="Línea de tendencia")

plt.title("Tiempos promedios de ejecución por combinación de bucles")
plt.xlabel("Combinación de bucles")
plt.ylabel("Tiempo promedio (segundos)")
plt.grid(True, axis='y', ls="--")
plt.legend()
plt.savefig("tiempos_promedios.png")  # Guardar la gráfica en PNG
plt.close()

print("Gráficas generadas y guardadas como imágenes PNG.")