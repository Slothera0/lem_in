#include "node.h"
#include "libft.h"

t_room_type	set_type(char *line)
{
	if (ft_strncmp(line, "##start", ft_strlen(line)) == 0)
		return (START);
	if (ft_strncmp(line, "##end", ft_strlen(line)) == 0)
		return (END);
	return (NORMAL);
}
