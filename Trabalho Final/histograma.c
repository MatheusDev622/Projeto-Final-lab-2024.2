/* ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ ∗/
/* Aluno: João Victor Pequeno Damasceno                    ∗/
/∗ Matrícula: 2024.1045050081                              ∗/
/∗ Avaliação 04: Trabalho Final                            ∗/
/∗ 04.505.23 − 2024.2 − Prof. Daniel Ferreira              ∗/
/∗ Compilador: gcc 13.3.0                                  ∗/
/∗ ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ */

#include <stdio.h>
#include <stdlib.h>
#include "lib/pgm.h" // Inclui o arquivo de cabeçalho pgm.h

// Função para gerar o histograma
void generateHistogram(PGMImage *image, int histogram[256]) {
    // Inicializa o histograma com zeros
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }

    // Conta a frequência de cada valor de pixel
    int size = image->width * image->height;
    for (int i = 0; i < size; i++) {
        int pixelValue = image->pixels[i];
        histogram[pixelValue]++;
    }
}

// Função para exibir o histograma
void displayHistogram(int histogram[256]) {
    printf("Histograma:\n");
    for (int i = 0; i < 256; i++) {
        if (histogram[i] > 0) {
            printf("Intensidade %d: %d pixels\n", i, histogram[i]);
        }
    }
}

int main() {
    // Carrega a imagem PGM
    PGMImage image;
    readPGM("input_image.pgm", &image);

    // Gera o histograma
    int histogram[256];
    generateHistogram(&image, histogram);

    // Exibe o histograma
    displayHistogram(histogram);

    // Libera a memória da imagem
    free(image.pixels);

    return 0;
}