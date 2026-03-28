


int	is_a_num(char *str)
{
	int i  = 0;

	if (str[i] == '-')
		i++;

	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}

	if (i == 0)
		return (0);

	return (1);
}
