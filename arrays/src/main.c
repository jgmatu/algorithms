#include <stdio.h>
#include <stdint-gcc.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <err.h>

// Encontrar el segundo elemento mínimo del array.


#define MAX_VALUES 20

struct array_data
{
    int32_t values[MAX_VALUES];
    size_t size;
};

struct matrix_data
{
    struct array_data rows[MAX_VALUES];
    size_t size;
};

int search_min(const struct array_data *array, struct array_data *array_min)
{
    int min = INT16_MAX;

    for (uint32_t i = 0; i < array->size; ++i)
    {
        int discard = 0;

        for (uint32_t j = 0; j < array_min->size && !discard; ++j)
        {
            discard = array->values[i] == array_min->values[j];
        }
        if (!discard && array->values[i] < min)
        {
            min = array->values[i];
        }
    }
    array_min->values[array_min->size++] = min;
    return min;
}

int duplicated(const struct array_data *array, int32_t value)
{
    for (uint32_t i = 0; i < array->size; ++i)
    {
        if (array->values[i] == value)
            return 0;
    }
    return value;
}

int main(int argc, const char **argv)
{
    struct array_data array = { .size = MAX_VALUES, .values = { [ 0 ... MAX_VALUES - 1 ] = 0 } };
    struct array_data array_min = { .size = 0, .values = { [ 0 ... MAX_VALUES - 1 ] = -1 } };

    fprintf(stdout, "%s\n", "Values in array.");
    for (uint32_t i = 0; i < array.size; ++i)
    {
        while ((array.values[i] = duplicated(&array, random() % (2 * MAX_VALUES) + 1)) == 0);
        fprintf(stdout, "[%d]", array.values[i]);
    }
    fprintf(stdout, "%s\n", "");

    fprintf(stdout, "%s\n", "Sort from min value.");
    for (uint32_t i = 0; i < array.size; ++i)
    {
        fprintf(stdout, "[%d]", search_min(&array, &array_min));
    }
    fprintf(stdout, "%s\n", "");

    fprintf(stdout, "Second min value in array: %d\n", array_min.values[1]);
    return 0;
}