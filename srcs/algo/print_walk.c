#include "../../includes/distrib_ants.h"
#include "../../includes/node.h"
#include "../../srcs/vector/vector.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

void print_ant_move(unsigned int ant_id, const char *room_name);
int room_is_empty(t_distrib_ants *distrib, unsigned int assigned_ants, t_node *room);

int print_walk(t_distrib_ants *distrib, unsigned int assigned_ants)
{
    unsigned int finish_count;
    unsigned int move;
    finish_count = 0;

    while(finish_count < assigned_ants)
    {
        unsigned int max_step;

        max_step = 0;
        move = 0;
        for (unsigned int i = 0; i < assigned_ants; i++)
        {
            if (distrib[i].path && !distrib[i].arrived && distrib[i].path_step > max_step)
                max_step = distrib[i].path_step;
        }
        for (unsigned int step = max_step + 1; step > 0; step--)
        {
            for (unsigned int i = 0; i < assigned_ants; i++)
            {
                t_vector *path;
                t_node *room;

                if(distrib[i].arrived || distrib[i].path_step != step - 1)
                    continue;
                path = distrib[i].path;
                room = (t_node *)path->array[distrib[i].path_step + 1];
                if (room->type == END || room_is_empty(distrib, assigned_ants, room) == 1)
                {
                    print_ant_move(distrib[i].ants_id, room->name);
                    distrib[i].path_step += 1;
                    move = 1;
                    if (distrib[i].path_step + 1 >= path->size)
                    {
                        distrib[i].arrived = 1;
                        finish_count++;
                    }
                }
            }
        }
        if (move)
            printf("\n");
        else
            break;
    }
    return 0;
}



int room_is_empty(t_distrib_ants *distrib, unsigned int assigned_ants, t_node *room)
{
    t_vector *path;
    t_node *compare_room;

    if(!room)
        return (0);
    if (room->type == START || room->type == END)
        return (1);


    for(unsigned int i = 0; i < assigned_ants; i++)
    {
        if(!distrib[i].arrived && distrib[i].path && distrib[i].path_step > 0)
        {
            path = distrib[i].path;
            compare_room = (t_node *)path->array[distrib[i].path_step];
            if (room == compare_room)
                return (0);
        }
    }
    return (1);
}

void print_ant_move(unsigned int ant_id, const char *room_name)
{
    printf("L%u-%s ",ant_id,room_name);
}

