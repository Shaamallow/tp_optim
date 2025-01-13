#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "transfo.h"
#ifdef USE_CLOCK
#include <time.h>
#else
#include "cycles.h"
#endif

#ifdef USE_CLOCK
clock_t transform_image(char *source, char *curve, int light, char *dest)
#else
double transform_image(char *source, char *curve, int light, char *dest)
#endif
{
    FILE *in = fopen(source, "r");
    FILE *map = fopen(curve, "r");
    if (!in || !map) exit(1);

    int height, width, maxval;
    fscanf(in, "P5\n%d %d\n%d\n", &height, &width, &maxval);
    if (maxval > 255) exit(1);

    long size = width * height;
    unsigned char *source_image = malloc(size);
    unsigned char *dest_image = malloc(size);
    unsigned char lut[256];

    fread(lut, 1, 256, map);
    fread(source_image, 1, size, in);

    fclose(in);
    fclose(map);

#ifdef USE_CLOCK
    clock_t start = clock();
#else
    start_counter();
#endif
    transfo(width, height, source_image, dest_image, lut, light);
#ifdef USE_CLOCK
    clock_t t = clock() - start;
    printf("%ld clock cycles.\n", t);
#else
    double t = get_counter();
    printf("%f clock cycles.\n", t);
#endif

    FILE *out = fopen(dest, "w");
    fprintf(out, "P5\n%d %d\n%d\n", height, width, maxval);
    fwrite(dest_image, 1, size, out);
    fclose(out);

    free(source_image);
    free(dest_image);
    return t;
}

void run_transfo_file(FILE *tf) {
    char source[255], curve[255], dest[255];
    int light;
    while (fscanf(tf, "%s %s %d %s", source, curve, &light, dest) == 4) {
        transform_image(source, curve, light, dest);
    }
}

int main(int ac, char *av[]) {
    if (ac != 2) exit(1);
    FILE *tf = fopen(av[1], "r");
    if (!tf) exit(1);

    chdir(dirname(av[1]));
    run_transfo_file(tf);
    fclose(tf);
    return 0;
}

