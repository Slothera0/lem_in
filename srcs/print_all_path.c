#include "../srcs/vector/vector.h"
#include <stdio.h>

void print_path(t_vector *path);

void print_all_path(t_vector *all_path)
{
    unsigned int i;
    t_vector *path;

    i = 0;
    while(i < all_path->size)
    {
        path = (t_vector *)all_path->array[i];
        printf("PATH %u:\n", i);
        print_path(path);
        i++;
    }
}