// ./shm_test_throughput 4294967296 1 --> 4GB
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define SHM_NAME "/my_shm"
#define SHM_SIZE (1024ull * 1024ull *1024 * 10ull)  // 10GB
#define ARRAY_SIZE (1024ull * 1024ull * 7ull)  // 700MB
#define ITERATIONS 50
int main(int argc, char ** argv) {
    double arraysize = 1024 * 1024 * 1024 * 1;
    int iterations = ITERATIONS;
    int cores = 1;
    if(argc == 1){
	 printf("Default array size=1GB and Cores=1.\n");
	 printf("To run with different array size and cores run ./shm_test_throughput 1024 64.\n");
    }else{
    	arraysize = atof(argv[1]);
	cores = atoi(argv[2]);
	double sizeinGB = arraysize / (1024*1024*1024);
	printf("Array size: %.1f GB, iterations: %d, cores: %d \n", sizeinGB, iterations, cores);
    }
    int fd;
    char *ptr, *array;
    double total_time = 0.0;

    // Create the shared memory object
    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("shm_open failed");
        return 1;
    }
    // Configure the size of the shared memory object
    if (ftruncate(fd, SHM_SIZE) == -1) {
        perror("ftruncate failed");
        return 1;
    }

    // Map the shared memory object to the process's address space
    ptr = (char*)(mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }
    // Allocate memory for the array using malloc
    array = (char *) malloc(arraysize);
    if (array == NULL) {
    	perror("malloc failed");
       return 1;
    }
    // Perform the benchmark
    struct timespec start, end;
    //struct timeval st, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    //gettimeofday(&st,NULL);
    for (int i = 0; i < iterations; i++) {
	    #pragma omp parallel for
	    for (int j=0; j<cores; j++)
		   memcpy(ptr, array, arraysize/cores); 
    }
    //gettimeofday(&end,NULL);
    clock_gettime(CLOCK_MONOTONIC, &end);

    total_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    double throughput = (arraysize * iterations) / total_time;
    double throughput_gb_s = throughput / (1024*1024*1024);
    printf("Throughput: %f GB/s\n", throughput_gb_s);

    // Clean up
    munmap(ptr, SHM_SIZE);
    free(array);
    shm_unlink(SHM_NAME);
    close(fd);

    return 0;
}

