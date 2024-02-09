#include <stdio.h>
#include <sys/types.h>
#include <math.h>
#include <stdatomic.h>
#include <errno.h>
#include <err.h>
#include <time.h>
#include <string.h>

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

int32_t lineal_search(u_int32_t *arr, u_int32_t size, u_int32_t value)
{
    for (u_int32_t i = 0; i < size; ++i)
        if (arr[i] == value)
            return i;
    return -1;
}

int64_t difftimespec_us(const struct timespec after, const struct timespec before)
{
    return ((int64_t)after.tv_sec - (int64_t)before.tv_sec) * (int64_t) 1000000
         + ((int64_t)after.tv_nsec - (int64_t)before.tv_nsec) / 1000;
}

int main(int argn, char **argv)
{
    static u_int32_t test[SIZE_SAMPLE];
    u_int32_t size = SIZE_SAMPLE;
    u_int32_t elapsed_binary = 0;
    u_int32_t elapsed_linear = 0;

    fprintf(stdout, "%s\n", "Initializing data...");

    for (u_int32_t i = 0; i < size; ++i)
    {
        test[i] = i * 2; // Sorted value list, need it to use a binary search sort items.
    }

    {
        struct timespec now;

        if (clock_gettime(CLOCK_REALTIME, &now) != 0)
            err(1, "Error getting mark time: %s\n", strerror(errno));

        int32_t index = binary_search(test, size, __UINT32_MAX__ / 2 + 1);

        struct timespec binary_mark;

        if (clock_gettime(CLOCK_REALTIME, &binary_mark) != 0)
            err(1, "Error getting mark time: %s\n", strerror(errno));

        u_int32_t elapsed = difftimespec_us(binary_mark, now);

        if (index >= 0)
            fprintf(stdout, "Value found index %d value %u time %d us.\n", index, test[index], elapsed);
        else
            fprintf(stdout, "%s time %d us.\n", "Value not found!", elapsed);

        elapsed_binary = elapsed;
    }

    {
        struct timespec now;

        if (clock_gettime(CLOCK_REALTIME, &now) != 0)
            err(1, "Error getting mark time: %s\n", strerror(errno));

        int32_t index = lineal_search(test, size, __UINT32_MAX__ / 2 + 1);

        struct timespec binary_mark;

        if (clock_gettime(CLOCK_REALTIME, &binary_mark) != 0)
            err(1, "Error getting mark time: %s\n", strerror(errno));

        u_int32_t elapsed = difftimespec_us(binary_mark, now);

        if (index >= 0)
            fprintf(stdout, "Value found index %d value %u time %d us.\n", index, test[index], elapsed);
        else
            fprintf(stdout, "%s time %d us.\n", "Value not found!", elapsed);

        elapsed_linear = elapsed;
    }

    fprintf(stdout, "Relative performance binary search is %f times faster in this case of use.\n", ((float) elapsed_linear) / ((float) elapsed_binary));
    return 0;
}