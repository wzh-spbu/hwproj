#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_PAUSE_EVERY 10000
#define DEFAULT_PAUSE_TIME_MS 100

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Lack of parameter");
        return EXIT_FAILURE;
    }

    unsigned long memory_size_mb = strtoul(argv[1], NULL, 10);
    char *access_type = argv[2];
    unsigned long pause_every = (argc >= 4) ? strtoul(argv[3], NULL,10) : DEFAULT_PAUSE_EVERY;
    unsigned long pause_time_ms = (argc >= 5) ? strtoul(argv[4], NULL,10) : DEFAULT_PAUSE_TIME_MS;

    int is_write;
    if (strcmp(access_type, "write") == 0) {
        is_write = 1;
    } else if (strcmp(access_type, "read") == 0) {
        is_write = 0;
    }

    size_t memory_size_bytes = memory_size_mb * 1024 * 1024;
    size_t page_size = 4 * 1024; // 4 KiB
    size_t step = page_size / sizeof(char);

    printf("Allocating %lu MB of memory...\n", memory_size_mb);
    char *memory = malloc(memory_size_bytes);
    printf("Memory allocation successful. Starting %s operations...\n", access_type);

    unsigned long access_count = 0;
    for (size_t i = 0; i < memory_size_bytes; i += step * sizeof(char)) {
        if (is_write) {
            memory[i] = (char)(i % 256);
        } else {
            volatile char temp = memory[i];
            //(void)temp;
        }
        access_count++;
        if (access_count % pause_every == 0) {
            printf("Pausing for %lu ms after %lu accesses...\n", pause_time_ms, access_count);
            usleep(pause_time_ms);
        }
    }

    printf("Complete. Cleaning up...\n");
    free(memory);
    return EXIT_SUCCESS;
}