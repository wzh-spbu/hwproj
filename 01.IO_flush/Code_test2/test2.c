#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <your_name>\n", argv[0]);
    } else {
        printf("Hello, %s!\n", argv[1]);
    }
    return 0;
}
