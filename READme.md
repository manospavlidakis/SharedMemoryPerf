#Benchmark to evaluate shared memory throughput
##Using 1 thread and N threads (N=#cores)

##Results
| Benchmark suite  	| Processor - # of threads used in the evaluation 	|               	|                	|                 	|
|------------------	|:-----------------------------------------------:	|:-------------:	|:--------------:	|:---------------:	|
|                  	|                   AMD-1 (MB/s)                  	| AMD-64 (MB/s) 	| INTEL-1 (MB/s) 	| INTEL-64 (MB/s) 	|
| STREAM Best Rate 	|                      15.10                      	|     86.30     	|      11.40     	|      34.90      	|
| memcpy SHMEM     	|                      21.40                      	|      82.1     	|      11.60     	|        39       	|
| memcpy MALLOC    	|                      21.50                      	|      30.6     	|      11.20     	|       38.1      	|

##Servers
|                                           	| **AMD server** 	| **Intel server** 	|
|-------------------------------------------	|----------------	|------------------	|
| CPU type                                  	|     EPYC 7551P 	|  Xeon E5-2620 v4 	|
| CPU Frequency                             	|           2GHz 	|         2.10 GHz 	|
| Physical cores                            	|             32 	|                8 	|
| Hardware Threads                          	|             64 	|               16 	|
| L3 cache                                  	|        8192 KB 	|         20480 KB 	|
| # sockets                                 	|              1 	|                1 	|
| # NUMA nodes                              	|              4 	|                1 	|
| # memory controllers per NUMA node        	|              1 	|                1 	|
| # channels / memory controller            	|              2 	|                4 	|
| Peak Transfer Rate of DDR4                	|      2666 MT/s 	|        2133 MT/s 	|
| Peak Transfer Rate of DDR4                	|      21.3 GB/s 	|          17 GB/s 	|
| Max Memory Bandwidth (According to specs) 	|       170 GB/s 	|        68.3 GB/s 	|
