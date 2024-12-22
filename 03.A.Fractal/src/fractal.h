#ifndef FRACTAL_H
#define FRACTAL_H

#include "image.h"

void empty_fractal(image_p picture, int depth);
void julia_fractal(image_p picture, double c_real, double c_imag, int max_iter);
void draw_sierpinski_carpet(image_p picture,
                                   pixel_coord x,
                                   pixel_coord y,
                                   pixel_coord size,
                                   int depth);
#endif // FRACTAL_H
