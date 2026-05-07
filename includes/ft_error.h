#ifndef ERROR_H
# define ERROR_H

#ifndef T_ERROR
# define T_ERROR
typedef enum e_error
{
	MALLOC_ERROR = -1,
	PARSE_ERROR = -2,
} t_error ;
#endif

int	ft_error(int statut);

#endif