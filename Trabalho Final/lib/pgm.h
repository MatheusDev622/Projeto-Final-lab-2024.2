
#ifndef _PGM_H
#define _PGM_H 1

typedef struct {
    char format[3];             // Formato da imagem: "P2" (ASCII) ou "P5" (binário)
    int width, height;          // Largura e altura da imagem
    unsigned char maxval;       // Valor máximo de intensidade dos pixels de 0 a 255 (use 'short' ao inves de 'char' para o range completo do PGM [0, 65535])
    unsigned char *pixels;      // Array que armazena os valores dos pixels (use 'short' ao inves de 'char' para o range completo do PGM [0, 65535])
} PGMImage;

int readPGM(const char *filepath, PGMImage *image);

int makePGM(const char *filename, PGMImage *image);

void switchPGMType(PGMImage *image);

int *getHistogram(PGMImage image);

void freePGM(PGMImage *image);

#endif