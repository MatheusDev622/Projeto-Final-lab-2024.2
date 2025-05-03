/* ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ ∗/
/* Aluno: Matheus Rodrigues Ferreira                       ∗/
/∗ Matrícula: 2024.1045050430                              ∗/
/∗ Avaliação 04: Trabalho Final                            ∗/
/∗ 04.505.23 − 2024.2 − Prof. Daniel Ferreira              ∗/
/∗ Compilador: gcc 13.3.0                                  ∗/
/∗ ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "lib/pgm.h" // Inclui o arquivo de cabeçalho pgm.h
#include "lib/utils.h" // Inclui o arquivo de cabeçalho utils.h

// Função para aplicar o algoritmo k-means à imagem
int kmeansClustering(PGMImage *image, int k, int maxIter) {
    int size = image->width * image->height;
    float *centroids = allocMemFloat(k);
    float *old_centroids = allocMemFloat(k);
    unsigned char *labels = allocMemUC(size);

    int iterations = 0;

    // Inicializa os centróides com valores aleatórios
    srand(time(NULL));
    for (int i = 0; i < k; i++) {
        centroids[i] = image->pixels[rand() % size];
    }

    // Executa o k-means
    for (int iter = 0; iter < maxIter; iter++) {
        // Atribui cada pixel ao cluster mais próximo
        for (int i = 0; i < size; i++) {
            int pixelValue = image->pixels[i];
            int minIndex = 0;
            int minDist = fabs(pixelValue - centroids[0]);

            for (int j = 1; j < k; j++) {
                int dist = abs(pixelValue - centroids[j]);
                if (dist < minDist) {
                    minDist = dist;
                    minIndex = j;
                }
            }

            labels[i] = minIndex;
        }

        // Recalcula os centróides
        int *sums = (int *)calloc(k, sizeof(int));
        int *counts = (int *)calloc(k, sizeof(int));
        for (int i = 0; i < size; i++) {
            sums[labels[i]] += image->pixels[i];
            counts[labels[i]]++;
        }
        for (int j = 0; j < k; j++) {
            old_centroids[j] = centroids[j];
            if (counts[j] > 0) {
                centroids[j] = sums[j] / (float)counts[j]; 
            }
        }

        free(sums);
        free(counts);

        iterations++;
        if (iter != 0) {
            if (checkDiffOnThreshold(old_centroids, centroids, k, 0.5)) break;
        }
    }

    // Aplica a clusterização à imagem
    for (int i = 0; i < size; i++) {
        image->pixels[i] = centroids[labels[i]];
    }

    // Libera a memória alocada
    free(centroids);
    free(labels);

    return iterations;
}