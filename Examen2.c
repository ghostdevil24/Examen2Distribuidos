#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void reiniciarMatriz(int n, int **matrizC) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrizC[i][j] = 0;
        }
    }
}

double *medirTiempos(int n) {
    int **matrizA = (int **)malloc(n * sizeof(int *));
    int **matrizB = (int **)malloc(n * sizeof(int *));
    int **matrizC = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        matrizA[i] = (int *)malloc(n * sizeof(int));
        matrizB[i] = (int *)malloc(n * sizeof(int));
        matrizC[i] = (int *)malloc(n * sizeof(int));
    }
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrizA[i][j] = rand() % 100;
            matrizB[i][j] = rand() % 100;
        }
    }

    double *tiempos = (double *)malloc(6 * sizeof(double));
    struct timespec inicio, fin;

    // Combinación 1: i, j, k
    reiniciarMatriz(n, matrizC);
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &fin);
    tiempos[0] = (fin.tv_sec - inicio.tv_sec) + (fin.tv_nsec - inicio.tv_nsec) / 1e9;

    // Combinación 2: i, k, j
    reiniciarMatriz(n, matrizC);
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            for (int j = 0; j < n; ++j) {
                matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &fin);
    tiempos[1] = (fin.tv_sec - inicio.tv_sec) + (fin.tv_nsec - inicio.tv_nsec) / 1e9;

    // Combinación 3: j, i, k
    reiniciarMatriz(n, matrizC);
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < n; ++k) {
                matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &fin);
    tiempos[2] = (fin.tv_sec - inicio.tv_sec) + (fin.tv_nsec - inicio.tv_nsec) / 1e9;

    // Combinación 4: j, k, i
    reiniciarMatriz(n, matrizC);
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &fin);
    tiempos[3] = (fin.tv_sec - inicio.tv_sec) + (fin.tv_nsec - inicio.tv_nsec) / 1e9;

    // Combinación 5: k, i, j
    reiniciarMatriz(n, matrizC);
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &fin);
    tiempos[4] = (fin.tv_sec - inicio.tv_sec) + (fin.tv_nsec - inicio.tv_nsec) / 1e9;

    // Combinación 6: k, j, i
    reiniciarMatriz(n, matrizC);
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int k = 0; k < n; ++k) {
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &fin);
    tiempos[5] = (fin.tv_sec - inicio.tv_sec) + (fin.tv_nsec - inicio.tv_nsec) / 1e9;

    for (int i = 0; i < n; ++i) {
        free(matrizA[i]);
        free(matrizB[i]);
        free(matrizC[i]);
    }
    free(matrizA);
    free(matrizB);
    free(matrizC);

    return tiempos;
}

int main() {
    int tamanos[] = {10, 100, 500, 1000, 3000, 5000, 10000};
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);

    FILE *archivo = fopen("tiempos.csv", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    fprintf(archivo, "tamaño,ijk,ikj,jik,jki,kij,kji\n");

    for (int i = 0; i < num_tamanos; ++i) {
        int n = tamanos[i];
        double *tiempos = medirTiempos(n);

        printf("Tamaño de matriz: %d\n", n);
        printf("ijk: %.12f segundos\n", tiempos[0]);
        printf("ikj: %.12f segundos\n", tiempos[1]);
        printf("jik: %.12f segundos\n", tiempos[2]);
        printf("jki: %.12f segundos\n", tiempos[3]);
        printf("kij: %.12f segundos\n", tiempos[4]);
        printf("kji: %.12f segundos\n", tiempos[5]);
        printf("\n");

        fprintf(archivo, "%d,%.15f,%.15f,%.15f,%.15f,%.15f,%.15f\n", n, tiempos[0], tiempos[1], tiempos[2], tiempos[3], tiempos[4], tiempos[5]);

        free(tiempos);
    }

    fclose(archivo);
    printf("Tiempos guardados en 'tiempos.csv'.\n");

    return 0;
}
