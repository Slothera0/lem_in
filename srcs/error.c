#include "error.h"
#include "libft.h"

void	ft_error(int statut)
{
	switch (statut)
	{
	case MALLOC:
		ft_putstr_fd("Error: Malloc failed", 2);
		break;
	
	}
}
