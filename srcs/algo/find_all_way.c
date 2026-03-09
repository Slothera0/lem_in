#include "lem_in.h"
#include "node.h"
#include "vector.h"

static void	rec_find_all_way(t_node *start, t_vector *all_way);

void	find_all_way(t_lem_in *data)
{
	t_vector	*all_way;
	t_node		*start;

	all_way = vec_create(10);
	if (!all_way)
		error();
	
	start = get_start(data->node);

	rec_find_all_way(start, all_way);
}

static void	rec_find_all_way(t_node *start, t_vector *all_way)
{
	t_vector	*way;
	t_node		*current;

	way = vec_create(10);
	if (!way)
		error();
	
	current = start;
	
	while(current->type != END)
	{
		if (current->links->size == 0)
			error(); // fin de la route
		
		way = vec_append(way, current);
		if (!way)
			error();
		
		
	}
}

/* 
Solution possible :

all_way[] contient un vec avec start

rec_find_all_way(t_node *current, t_vector *all_way)
{
	Si il n'existe aucune room pas deja emprunte lié a la derniere
		stop
	
	Sinon
		le premier chemin supllémentaire possible est ajouté au chemin actuel
		les autres créent tous une copie du vecteur actuel et s'ajoute a cette copie puis ajoute la copi a all_way
}

all_way[] = tous les chemins essayé
remove ceux avec un dernier elem qui est pas de type END

all_way[] = tous les chemins qui menent a la sortie


*/