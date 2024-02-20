#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRAY_SIZE (1024 * 1024 * 10)  // 10MB
#define ITERATIONS 1000

int main(int argc, char *argv[]) {
    double total_time = 0.0;
    char *src, *dst;
    double size;
    if (argc != 2) {
        printf("Usage: %s <size>\n", argv[0]);
        return 1;
    }

    size = atoi(argv[1]);
    double size_gb = size / 1073741824;
    printf("Size: %.3f GB\n", size_gb);
    src = (char *) malloc(size);
    dst = (char *) malloc(size);
    if (src == NULL || dst == NULL) {
        perror("malloc failed");
        return 1;
    }
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < ITERATIONS; i++) {
        memcpy(dst, src, size);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    total_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    double throughput = (size * ITERATIONS) / total_time;
    double throughput_gb_s = throughput / (1024*1024*1024);
    printf("Throughput: %f GB/s\n", throughput_gb_s);

    free(src);
    free(dst);
    return 0;
}

