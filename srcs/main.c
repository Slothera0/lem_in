#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

char *get_next_line(int fd);

int	main(int argc, char *argv[])
{
	if (argc == 1)
		return (0);

	int fd = open(argv[1], O_RDONLY);
	
	char *s = NULL;
	s = get_next_line(fd);

	while(s)
	{
		printf("%s", s);
		s = get_next_line(fd);
	}

	return (0);
}