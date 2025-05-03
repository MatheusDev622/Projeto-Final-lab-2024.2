/* ******************************************************************************** */
/* Aluno: Oto Ribeiro Serafim                              */
/* Matrícula: 2024.1045050189                              */
/* Avaliação 04: Trabalho Final                            */
/* 04.505.23 − 2024.2 − Prof. Daniel Ferreira              */
/* Compilador: gcc 13.3.0                                  */
/* ******************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/utils.h"

#define MAX_LINE_LENGTH 1024

// Estrutura para armazenar os dados da imagem PGM
typedef struct {
    char format[3];             // Formato "P2" ou "P5"
    int width, height;          // Largura e Altura da imagem
    unsigned char maxval;       // De 0 a 255 (use 'short' ao invés de 'char' para o alcance completo do PGM [0, 65535])
    unsigned char *pixels;      // Dados dos pixels (use 'short' ao invés de 'char' para o alcance completo do PGM [0, 65535])
} PGMImage;

/**
 * @brief Função para ler um arquivo PGM
 * 
 * @param filepath 
 * @param image 
 * @return int 
 */
int readPGM(const char *filepath, PGMImage *image) {
    FILE *file;
    if ((file = fopen(filepath, "rb")) == NULL) {
        printf("Erro ao abrir o arquivo");
        return -1;
    }

    // Ler o formato (P2 ou P5)
    if (fscanf(file, "%2s", image->format) != 1) {
        printf("Erro ao ler o tipo do PGM: %s\n", filepath);
        fclose(file);
        return -1;
    }

    // Validar o formato
    if (strcmp(image->format, "P2") && strcmp(image->format, "P5")) {
        printf("Não é um arquivo PGM válido (Esperado P2 ou P5)\n");
        fclose(file);
        return -1;
    }

    // Ler largura, altura e maxval
    char line[MAX_LINE_LENGTH];
    int pixelIndex = 0;
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (line[0] == '#') continue; // Ignorar comentários
        if (sscanf(line, "%d %d", &image->width, &image->height) == 2) break; // Ler largura e altura
    }

    // Ler maxval
    fgets(line, MAX_LINE_LENGTH, file);
    sscanf(line,"%hhd", &image->maxval);

    // Alocar memória para os dados dos pixels
    int size = image->width * image->height;
    if ((image->pixels = allocMemUC(size)) == NULL) {
        printf("Memória insuficiente!\n");
        fclose(file);
        return -1;
    }

    // Ler os dados dos pixels
    if (!strcmp(image->format, "P5")) {
        // Formato binário (P5)
        fread(image->pixels, sizeof(unsigned char), size, file);
    } else if (!strcmp(image->format, "P2")) {
        // Formato ASCII (P2)
        while (fgets(line, MAX_LINE_LENGTH, file)) {
            char pixel[3];
            char ch;
            for (int k = 0, count = 0; ch != '\n'; k++) {
                ch = line[k];
                if (ch != ' ') {
                    pixel[count++] = ch;
                } else {
                    image->pixels[pixelIndex++] = (unsigned char) atoi(pixel);
                    count = 0;
                }
            }
        }
    }
    fclose(file);
    return 0;
}

/**
 * @brief Função para escrever um arquivo PGM
 * 
 * @param filename 
 * @param image 
 * @return int 
 */
int makePGM(const char *filename, const PGMImage *image) {
    int size = image->width * image->height;
    FILE *file;
    if ((file = fopen(filename, "w+")) == NULL) {
        printf("Erro ao criar o arquivo");
        return 1;
    }

    fprintf(file, "%s\n", image->format);
    fprintf(file, "%d %d\n", image->width, image->height);
    fprintf(file, "%hd\n", image->maxval);
    if (image->format[1] == '5') {
        fwrite(image->pixels, sizeof(unsigned char), size, file);
    } else if (image->format[1] == '2') {
        for (int k = 0; k < size; k++) {
            fprintf(file, "%hd", image->pixels[k]);
            if (!((k + 1) % (image->width)) && k + 1 != size) {
                fprintf(file, "\n");
            } else {
                fprintf(file, " ");
            }
        }
    }
    fclose(file);
    return 0;
}

/**
 * @brief Função para alternar entre os formatos PGM (P2 <-> P5)
 * 
 * @param image 
 */
void switchPGMType(PGMImage *image) {
    image->format[1] = (image->format[1] == '2') ? '5' : '2';
}

/**
 * @brief Retorna um histograma da imagem.
 * 
 * @param image 
 * @return int* 
 */
int *getHistogram(PGMImage image) {
    int *histogram = allocMemInt(image.maxval + 1);
    for (int k = 0; k < image.height * image.width; k++) histogram[image.pixels[k]]++;
    return histogram;
}

/**
 * @brief Função para liberar a memória alocada para PGMImage
 * 
 * @param image 
 */
void freePGM(PGMImage *image) {
    if (image->pixels != NULL) {
        free(image->pixels);
    }
}