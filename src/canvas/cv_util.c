#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/canvas.h"

void
canvas_destroy(canvas *cv) {
  bzero((void *)cv->d, CanvasSize(cv->width, cv->height) * sizeof(uchar));
  free(cv->d);
  cv->d = NULL;
}

void
n_canvas_destroy(n_canvas *ncv) {
  bzero((void *)ncv->n, CanvasSize(ncv->width, ncv->height) * sizeof(double));
  free(ncv->n);
  ncv->n = NULL;
}
