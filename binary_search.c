#include <stdio.h>
#include <sys/types.h>
#include <math.h>

#define SIZE_SAMPLE __UINT32_MAX__ / 2

int64_t binary_search(u_int32_t *arr, u_int32_t size, u_int32_t value)
{
    u_int32_t middle = size / 2;
    u_int32_t min = 0;
    u_int32_t max = size - 1;
    u_int32_t iterations = 0;
    u_int32_t max_iterations = log2(size) + 1;

    while (arr[middle] != value && iterations < max_iterations)
    {
        if (arr[middle] < value)
        {
            min = middle + 1;
        }
        if (arr[middle] > value)
        {
            max = middle;
        }
        middle = (max + min) / 2;
        iterations = iterations + 1;
    }
    return (iterations < max_iterations) ? middle : -1;
}

int main(int argn, char **argv)
{
    u_int32_t test[SIZE_SAMPLE];
    u_int32_t size = sizeof(test) / sizeof(u_int32_t);

    for (u_int32_t i = 0; i < size; ++i)
    {
        test[i] = i * 2;
    }
    int64_t index = binary_search(test, size, 77238U);

    fprintf(stdout, "Value found index: %ld\n", index);
}