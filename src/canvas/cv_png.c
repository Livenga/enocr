#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <png.h>
#include "../../include/canvas.h"

int
pnread(const char *png_path,
       canvas     *cv) {
  int i;

  FILE        *png_fp;
  png_structp png_ptr;
  png_infop   info_ptr;
  uchar       **png_data;

  if((png_fp = fopen(png_path, "rb")) == NULL) {
    perror(png_path);
    return EOF;
  }

  png_ptr  = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  info_ptr = png_create_info_struct(png_ptr);

  png_init_io(png_ptr, png_fp);

  png_read_info(png_ptr, info_ptr);

  cv->width  = png_get_image_width(png_ptr, info_ptr);
  cv->height = png_get_image_height(png_ptr, info_ptr);
  cv->d = (uchar *)calloc(CanvasSize(cv->width, cv->height), sizeof(uchar));

  png_data = (uchar **)calloc(cv->height, sizeof(uchar *));
  for(i = 0; i < cv->height; i++)
    png_data[i] = (uchar *)calloc(cv->width, sizeof(uchar));

  png_read_image(png_ptr, (png_bytepp)png_data);
  png_read_end(png_ptr, info_ptr);

  png_destroy_info_struct(png_ptr, &info_ptr);
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

  fclose(png_fp);

  for(i = 0; i < cv->height; i++) {
    memmove((void *)cv->d + (i * cv->width),
        (const void *)png_data[i], sizeof(uchar) * cv->width);
    bzero((void *)png_data[i], sizeof(uchar) * cv->width);
    free(png_data[i]);
    png_data[i] = NULL;
  }
  free(png_data);
  png_data = NULL;

  return 0;
}

int
pnwrite(const char *png_path,
        const canvas cv) {
  int i;

  FILE        *png_fp;
  png_structp png_ptr;
  png_infop   info_ptr;
  uchar       **png_data;

  if((png_fp = fopen(png_path, "wb")) == NULL) {
    perror(png_path);
    return EOF;
  }

  png_ptr  = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  info_ptr = png_create_info_struct(png_ptr);

  png_init_io(png_ptr, png_fp);

  png_set_IHDR(png_ptr, info_ptr,
      cv.width, cv.height, 8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_data = (uchar **)calloc(cv.height, sizeof(uchar *));
  for(i = 0; i < cv.height; i++) {
    png_data[i] = (uchar *)calloc(cv.width, sizeof(uchar));
    memmove((void *)png_data[i], (const void *)cv.d + (i * cv.width),
        sizeof(uchar) * cv.width);
  }

  png_write_info(png_ptr, info_ptr);
  png_write_image(png_ptr, (png_bytepp)png_data);
  png_write_end(png_ptr, info_ptr);
  fclose(png_fp);

  for(i = 0; i < cv.height; i++) {
    bzero((void *)png_data[i], sizeof(uchar) * cv.width);
    free(png_data[i]);
    png_data[i] = NULL;
  }
  free(png_data);
  png_data = NULL;

  return 0;
}

int
pnwrite_from_ncv(const char *png_path,
                 const n_canvas ncv) {
  int i, j;

  FILE        *png_fp;
  png_structp png_ptr;
  png_infop   info_ptr;
  uchar       **png_data;

  if((png_fp = fopen(png_path, "wb")) == NULL) {
    perror(png_path);
    return EOF;
  }

  png_ptr  = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  info_ptr = png_create_info_struct(png_ptr);

  png_init_io(png_ptr, png_fp);

  png_set_IHDR(png_ptr, info_ptr,
      ncv.width, ncv.height, 8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_data = (uchar **)calloc(ncv.height, sizeof(uchar *));
  for(i = 0; i < ncv.height; i++) {
    png_data[i] = (uchar *)calloc(ncv.width, sizeof(uchar));
    for(j = 0; j < ncv.width; j++)
      png_data[i][j] = (uchar)(ncv.n[i * ncv.width + j] * 255.0);
  }

  png_write_info(png_ptr, info_ptr);
  png_write_image(png_ptr, (png_bytepp)png_data);
  png_write_end(png_ptr, info_ptr);
  fclose(png_fp);

  for(i = 0; i < ncv.height; i++) {
    bzero((void *)png_data[i], sizeof(uchar) * ncv.width);
    free(png_data[i]);
    png_data[i] = NULL;
  }
  free(png_data);
  png_data = NULL;

  return 0;
}
