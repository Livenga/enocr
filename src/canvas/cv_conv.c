#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/canvas.h"

void
cv2normalize(n_canvas *dest,
             const canvas src) {
  int i, j;

  dest->width  = src.width;
  dest->height = src.height;
  dest->n      =
    (double *)calloc(CanvasSize(src.width, src.height), sizeof(double));

  for(i = 0; i < src.height; i++)
    for(j = 0; j < src.width; j++)
      dest->n[i * src.width + j] = (double)src.d[i * src.width + j] / 255.0;
}

void
cv2reverse(canvas *dest) {
  int i, j;
  for(i = 0; i < dest->height; i++)
    for(j = 0; j < dest->width; j++)
      dest->d[i * dest->width + j] =
        0xFF - dest->d[i * dest->width + j];
}
