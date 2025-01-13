#include <omp.h>

void copy(int w, int h, unsigned char *src, unsigned char *dest) {
  int i, j;

  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      dest[j * w + i] = src[j * w + i];
    }
  }
}

void light(int w, int h, unsigned char *img, unsigned char val) {
  int size = w * h;
#pragma omp parallel for
  for (int i = 0; i < size; i++) {
    img[i] = ((int)img[i] + val > 255) ? 255 : img[i] + val;
  }
}

void curve(int w, int h, unsigned char *img, unsigned char *lut) {
  int size = w * h;
#pragma omp parallel for
  for (int i = 0; i < size; i++) {
    img[i] = lut[img[i]];
  }
}

void transfo(int w, int h, unsigned char *src, unsigned char *lut,
             unsigned char val) {
  curve(w, h, src, lut);
  light(w, h, src, val);
}
