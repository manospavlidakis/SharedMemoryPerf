#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ITERATIONS 100

int main(int argc, char *argv[]) {
    double total_time = 0.0;
    char *src, *dst;
    double size;
    int cores;
    if (argc != 3) {
        printf("Usage: %s <size>, %s <cores>\n", argv[0]);
        return 1;
    }

    size = atof(argv[1]);
    cores = atoi(argv[2]);
    double size_gb = size / 1073741824;
    printf("Size: %.3f GB, Cores: %d\n", size_gb,cores);
    src = (char *) malloc(size);
    dst = (char *) malloc(size);
    if (src == NULL || dst == NULL) {
        perror("malloc failed");
        return 1;
    }
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < ITERATIONS; i++) {
	#pragma omp parallel for
	for (int j=0; j<cores; j++)
        	memcpy(dst, src, size/cores);
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

