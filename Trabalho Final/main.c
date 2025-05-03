
// C Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Project Headers
#include "lib/pgm.h"
#include "lib/kmeans.h"
#include "lib/utils.h"

int main(int argc, char const *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <imagemEntrada.pgm> <imagemSaida.pgm> <k>\n", argv[0]);
        exit(1);
    }

    PGMImage image;
    int k = atoi(argv[3]);

    char relative_path[1024];
    sprintf(relative_path, "database/dataset_Herlev_reduzido_PGM/");

    // Lê a imagem de entrada
    if (readPGM(strcat(relative_path, argv[1]), &image) != 0) {
        printf("Erro ao ler a imagem de entrada.\n");
        exit(2);
    }

    // Aplica o k-means à imagem
    kmeansClustering(&image, k, 30); // 30 iterações

    // Salva a imagem resultante
    sprintf(relative_path, "output/");
    makePGM(strcat(relative_path, argv[2]), &image);

    // Libera a memória alocada para os pixels
    freePGM(&image);

    return 0;
}