#include "libft.h"

void	ft_put_vecstr(void *data)
{
  char *s = data;
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], 1);
		i++;
	}
}
