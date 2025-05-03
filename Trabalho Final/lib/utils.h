/* ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ ∗/
/ * Aluno: Oto Ribeiro Serafim                              ∗/
/∗ Matrícula: 2024.1045050189                              ∗/
/∗ Avaliação 04: Trabalho Final                            ∗/
/∗ 04.505.23 − 2024.2 − Prof. Daniel Ferreira              ∗/
/∗ Compilador: gcc 13.3.0                                  ∗/
/∗ ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ */

#ifndef UTILS_H
#define UTILS_H 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned char *allocMemUC(unsigned int qtd);

int *allocMemInt(unsigned int qtd);

float *allocMemFloat(unsigned int qtd);

int checkDiffOnThreshold(float *v1, float *v2, int size, float threshold);

void printArrayUnsignedChar(unsigned char *arr, int size);

void printMatrixUnsignedChar(unsigned char *pm, int rows, int cols);

#endif