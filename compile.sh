#gcc simple_shm2.cpp -lrt -o shm_test_throughput
rm -rf memcpy_shm_exec;  gcc memcpy_shm.c -lrt -o memcpy_shm_exec
rm -rf memcpy_malloc_exec;  gcc memcpy_malloc.c -lrt -o memcpy_malloc_exec
rm -rf memcpy_shm_openmp_exec; gcc memcpy_shm_openmp.c -O2  -fopenmp -lrt -o memcpy_shm_openmp_exec
rm -rf memcpy_malloc_openmp_exec; gcc memcpy_malloc_openmp.c -O2  -fopenmp -lrt -o memcpy_malloc_openmp_exec
