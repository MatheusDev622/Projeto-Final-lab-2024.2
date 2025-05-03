#ifndef _KMEANS_H
#define _KMEANS_H 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pgm.h"

int kmeansClustering(PGMImage *image, int k, int maxIter);

#endif