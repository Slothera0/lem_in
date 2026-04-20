#include "libft.h"

void	remove_endline(char *str)
{
	size_t len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}