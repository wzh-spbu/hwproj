#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "fractal.h"
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <output_file> <fractal_type> <depth>\n", argv[0]);
        printf("Example: %s sierpinski.pgm sierpinski 4\n", argv[0]);
        return 1;
    }

    const char *output_file = argv[1];
    const char *fractal_type = argv[2];
    int depth = atoi(argv[3]);

    image_p img = create_image(300, 300);

    if (strcmp(fractal_type, "sierpinski") == 0) {
        empty_fractal(img, depth);
    } else if (strcmp(fractal_type, "julia") == 0) {
        double c_real = -0.7;
        double c_imag = 0.27015;
        if (argc >= 6) {
            c_real = atof(argv[4]);
            c_imag = atof(argv[5]);
        }
        julia_fractal(img, c_real, c_imag, depth);
    } else {
        printf("Unknown fractal type: %s\n", fractal_type);
        printf("Supported types: sierpinski, julia\n");
        free_image(img);
        return 1;
    }

    save_pgm(img, output_file);
    printf("Fractal saved to %s\n", output_file);

    free_image(img);
    return 0;
}
