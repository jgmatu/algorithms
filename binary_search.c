#include <stdio.h>
#include <sys/types.h>
#include <math.h>
#include <stdatomic.h>

#define SIZE_SAMPLE __UINT32_MAX__ / 2U

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
    u_int32_t test[SIZE_SAMPLE];
    u_int32_t size = sizeof(test) / sizeof(u_int32_t);

    for (u_int32_t i = 0; i < size; ++i)
    {
        test[i] = i * 2;
    }
    int32_t index = binary_search(test, size, 24142356U);
#if 0
static const char cachefiles_filecharmap[256] = {
	/* we skip space and tab and control chars */
	[33 ... 46] = 1,		/* '!' -> '.' */
	/* we skip '/' as it's significant to pathwalk */
	[48 ... 127] = 1,		/* '0' -> '~' */
};
#endif
    atomic_int counter = 0;

    fprintf(stdout, "Value found index: %d counter: %d\n", index, counter++);

    int value [1000] = {
         [0 ... sizeof(value) / sizeof(int) - 1] = 200,
    };

    for (int i = 0; i < sizeof(value) / sizeof(int); ++i)
    {
        fprintf(stdout, "%d", value[i]);
    }
    return 0;
}