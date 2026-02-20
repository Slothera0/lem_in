#include "error.h"
#include "libft.h"

int	ft_error(int statut)
{
	switch (statut)
	{
	case MALLOC_ERROR:
		ft_putstr_fd("Error: Malloc failed\n", 2);
		break;
	default:
		ft_putstr_fd("ERROR\n", 2);
		break;
	}

	return (1);
}
