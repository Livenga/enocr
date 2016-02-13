#ifndef __CANVAS_H
#define __CANVAS_H

#define CanvasSize(x, y) (x * y)

typedef unsigned char uchar;
typedef struct _canvas {
  size_t width, height;
  uchar *d;
} canvas;

typedef struct _n_canvas {
  size_t width, height;
  double *n;
} n_canvas;


/* src/canvas/cv_png.c */
extern int
pnread(const char *png_path,
       canvas     *cv);
extern int
pnwrite(const char *png_path,
        const canvas cv);
extern int
pnwrite_from_ncv(const char *png_path,
                 const n_canvas ncv);


/* src/canvas/cv_conv.c */
extern void
cv2normalize(n_canvas *dest,
             const canvas src);
extern void
cv2reverse(canvas *dest);

/* src/canvas/cv_util.c */
extern void
canvas_destroy(canvas *cv);
extern void
n_canvas_destroy(n_canvas *ncv);
#endif
