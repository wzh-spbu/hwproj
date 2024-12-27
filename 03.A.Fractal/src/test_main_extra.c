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
            ASSERT_EQ(0, get_pixel(utest_fixture->i, x, y));  // 验证每个像素是否为0
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

        int center_value = get_pixel(utest_fixture->i, 150, 150);
        if (depth == 1) {
            ASSERT_EQ(0, center_value);
        } else {
            ASSERT_EQ(0, center_value);
        }

        ASSERT_EQ(0, get_pixel(utest_fixture->i, 120, 120));
        ASSERT_EQ(0, get_pixel(utest_fixture->i, 180, 180));
        if (depth > 1) {
            ASSERT_EQ(255, get_pixel(utest_fixture->i, 150, 180));
            ASSERT_EQ(255, get_pixel(utest_fixture->i, 120, 150));
        }

        if (depth >= 3) {
            ASSERT_EQ(0, get_pixel(utest_fixture->i, 100, 100));
            ASSERT_EQ(0, get_pixel(utest_fixture->i, 200, 200));
        }

        if (depth == 4) {
            ASSERT_EQ(255, get_pixel(utest_fixture->i, 50, 50));
            ASSERT_EQ(255, get_pixel(utest_fixture->i, 250, 250));
        }
    }
}

















UTEST_MAIN();
