#include "../../includes/distrib_ants.h"
#include "../../includes/lem_in.h"
#include "../../includes/node.h"
#include "../../srcs/vector/vector.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

void print_ant_move(int ant_id, const char *room_name);

int print_walk(t_distrib_ants *distrib, unsigned int assigned_ants)
{
    unsigned int finish_count;
    unsigned int move;
    finish_count = 0;



    while(finish_count < assigned_ants)
    {
        move = 0;
        for (unsigned int i = 0; i < assigned_ants; i++)
        {
            t_vector *path;
            t_node *room;

            if(distrib[i].arrived)
                continue;
            path = distrib[i].path;

            if(!path || path->size == 0)
                continue;
            
            if(distrib[i].path_step + 1 >= path->size)
            {
                distrib[i].arrived = 1;
                finish_count++;
                continue;
            }
            room = (t_node *)path->array[distrib[i].path_step + 1];
            print_ant_move(distrib[i].ants_id, room->name);
            distrib[i].path_step += 1;
            move = 1;
        }
        if (move)
        {
            printf("\n");
        }

    }
    return 0;
}

void print_ant_move(int ant_id, const char *room_name)
{
    printf("L%d-%s ",ant_id,room_name);
}