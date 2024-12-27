#include <stdio.h>
#include "utest.h"
#include "image.h"
#include "fractal.h"

struct ImageTestFixture {
    image_p i;
};

UTEST_F_SETUP(ImageTestFixture) {
    utest_fixture->i = create_image(300, 300);
    ASSERT_NE((void *) utest_fixture->i, NULL);
}

UTEST_F_TEARDOWN(ImageTestFixture) {
    free_image(utest_fixture->i);
}

UTEST_F(ImageTestFixture, Set_Get_Pixel1){
    set_pixel(utest_fixture->i, 10, 10, 10);
    ASSERT_EQ(10, get_pixel(utest_fixture->i, 10, 10));
}

UTEST_F(ImageTestFixture, ClearImage) {
    clear_image(utest_fixture->i);
    for (pixel_coord y = 0; y < get_image_height(utest_fixture->i); ++y) {
        for (pixel_coord x = 0; x < get_image_width(utest_fixture->i); ++x) {
            ASSERT_EQ(0, get_pixel(utest_fixture->i, x, y));
        }
    }
}

UTEST_F(ImageTestFixture, Get_Image_Width_Height) {
    ASSERT_EQ(300, get_image_width(utest_fixture->i));
    ASSERT_EQ(300, get_image_height(utest_fixture->i));
}

UTEST_F(ImageTestFixture, SierpinskiCarpet) {
    int depths[] = {1, 2, 3, 4};
    for (int d = 0; d < 4; ++d) {
        int depth = depths[d];
        clear_image(utest_fixture->i);
        draw_sierpinski_carpet(utest_fixture->i, 0, 0, 300, depth);

        for (int dy = 0; dy < 3; ++dy) {
            for (int dx = 0; dx < 3; ++dx) {
                if (dx == 1 && dy == 1) {
                    continue;
                }

                pixel_coord center_x = dx * (300 / (3 * (depth + 1))) + 150;
                pixel_coord center_y = dy * (300 / (3 * (depth + 1))) + 150;
                
                ASSERT_EQ(0, get_pixel(utest_fixture->i, center_x, center_y));
            }
        }
    }
}

UTEST_F(ImageTestFixture, JuliaFractal) {
    clear_image(utest_fixture->i);

    double c_real = -0.8;
    double c_imag = 0.156;
    int max_iter = 300;

    julia_fractal(utest_fixture->i, c_real, c_imag, max_iter);

    ASSERT_EQ(0, get_pixel(utest_fixture->i, 0, 0));
    ASSERT_EQ(0, get_pixel(utest_fixture->i, 299, 299));

    pixel_data center_value = get_pixel(utest_fixture->i, 150, 150);
    ASSERT_NE(0, center_value);

    ASSERT_EQ(0, get_pixel(utest_fixture->i, 10, 10));

    free_image(utest_fixture->i);
}



















UTEST_MAIN();
