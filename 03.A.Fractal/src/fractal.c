#include "fractal.h"
#include "image.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void draw_sierpinski_carpet(image_p picture,
                                   pixel_coord x,
                                   pixel_coord y,
                                   pixel_coord size,
                                   int depth) {
    if (depth <= 0 || size < 1) {
        return;
    }

    pixel_coord new_size = size / 3;
    if (new_size == 0) {
        return;
    }

    for (pixel_coord row = y + new_size; row < y + 2 * new_size; ++row) {
        for (pixel_coord col = x + new_size; col < x + 2 * new_size; ++col) {
            set_pixel(picture, col, row, 0);
        }
    }

    for (int dy = 0; dy < 3; ++dy) {
        for (int dx = 0; dx < 3; ++dx) {
            if (dx == 1 && dy == 1) {
                continue;
            }
            draw_sierpinski_carpet(picture,
                                   x + dx * new_size,
                                   y + dy * new_size,
                                   new_size,
                                   depth - 1);
        }
    }
}

void empty_fractal(image_p picture, int depth) {
    for (pixel_coord row = 0; row < get_image_height(picture); ++row) {
        for (pixel_coord col = 0; col < get_image_width(picture); ++col) {
            set_pixel(picture, col, row, 255);
        }
    }

    pixel_coord size = (get_image_width(picture) < get_image_height(picture))
                       ? get_image_width(picture)
                       : get_image_height(picture);
    draw_sierpinski_carpet(picture, 0, 0, size, depth);
}

void julia_fractal(image_p picture, double c_real, double c_imag, int max_iter) {
    double x_min = -1.5;
    double x_max = 1.5;
    double y_min = -1.5;
    double y_max = 1.5;

    pixel_coord width = get_image_width(picture);
    pixel_coord height = get_image_height(picture);

    for (pixel_coord py = 0; py < height; ++py) {
        for (pixel_coord px = 0; px < width; ++px) {
            double x0 = x_min + (double)px / (width - 1) * (x_max - x_min);
            double y0 = y_min + (double)py / (height - 1) * (y_max - y_min);

            double x = x0;
            double y = y0;

            int iteration = 0;
            while (x * x + y * y <= 4.0 && iteration < max_iter) {
                double temp = x * x - y * y + c_real;
                y = 2.0 * x * y + c_imag;
                x = temp;
                iteration++;
            }

            if (iteration == max_iter) {
                set_pixel(picture, px, py, 0);
            } else {
                pixel_data color = (pixel_data)(255.0 * iteration / max_iter);
                set_pixel(picture, px, py, color);
            }
        }
    }
}
