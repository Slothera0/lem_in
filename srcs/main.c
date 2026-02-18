#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>


int	main()
{
	
	char *s = NULL;
	s = get_next_line(0);

	while(s)
	{
		printf("%s", s);
		s = get_next_line(0);
	}

	return (0);
}