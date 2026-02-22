#ifndef ERROR_H
# define ERROR_H

typedef enum e_error
{
	MALLOC_ERROR = -1,
	PARSE_ERROR = -2,
} t_error ;

int	ft_error(int statut);

#endif