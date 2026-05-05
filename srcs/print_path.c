#include "../srcs/vector/vector.h"
#include "../includes/node.h"
#include <stdio.h>


void print_path(t_vector *path)
{
    unsigned int i;
    t_node *current;

    i = 0;
    while (i < path->size)
    {
        current = (t_node *)path->array[i];
        printf("%s \n",current->name);
        i++;
    }
}