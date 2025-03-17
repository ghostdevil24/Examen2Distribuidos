import pandas as pd
import matplotlib.pyplot as plt

# Leer el archivo CSV con los tiempos
df = pd.read_csv("tiempos.csv")

# Mostrar los datos
print("Datos leídos del archivo CSV:")
print(df)

# Configuración de colores para las gráficas
colores = ['skyblue', 'lightgreen', 'lightcoral', 'orange', 'violet', 'gold']

# Gráficas de barras para cada tamaño de matriz
for i, tamaño in enumerate(df["tamaño"]):
    plt.figure(figsize=(10, 6))
    plt.bar(df.columns[1:], df.iloc[i, 1:], color=colores)
    plt.title(f"Tiempos de ejecución para tamaño de matriz {tamaño}")
    plt.xlabel("Combinación de bucles")
    plt.ylabel("Tiempo (segundos)")
    plt.grid(True, axis='y', ls="--")
    plt.savefig(f"tiempos_tamaño_{tamaño}.png")  # Guardar la gráfica en PNG
    plt.close()  # Cerrar la figura para liberar memoria

# Calcular el promedio de tiempos por combinación (excluyendo la columna "tamaño")
promedios = df.drop(columns=["tamaño"]).mean()

# Guardar los promedios en un archivo CSV
promedios.to_csv("promedios_tiempos.csv", header=["Tiempo promedio (segundos)"])

# Gráfica de barras para los promedios de tiempos
plt.figure(figsize=(10, 6))
plt.bar(promedios.index, promedios.values, color=colores)
plt.title("Promedio de tiempos por combinación de bucles")
plt.xlabel("Combinación")
plt.ylabel("Tiempo promedio (segundos)")
plt.grid(True, axis='y', ls="--")
plt.savefig("promedios_tiempos.png")  # Guardar la gráfica en PNG
plt.close()  # Cerrar la figura para liberar memoria

print("Gráficas y archivos CSV generados con éxito.")
