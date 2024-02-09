#include <stdio.h>
#include <sys/types.h>
#include <math.h>
#include <stdatomic.h>

#define SIZE_SAMPLE __UINT32_MAX__ / 2

int32_t binary_search(u_int32_t *arr, u_int32_t size, u_int32_t value)
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
    static u_int32_t test[SIZE_SAMPLE];
    u_int32_t size = SIZE_SAMPLE;

    for (u_int32_t i = 0; i < size; ++i)
    {
        test[i] = i * 2;
    }   
    int32_t index = binary_search(test, size, __UINT32_MAX__ / 2 + 1);

    if (index >= 0)
        fprintf(stdout, "Value found index: %d value: %u\n", index, test[index]);
    else
        fprintf(stdout, "%s\n", "Value not found!");
    return 0;
}