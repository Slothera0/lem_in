#include "rend.h"

int init_window(t_rend *rend_adr);
int start_rend(t_rend rend);

int main()
{
	t_rend rend;

	if (init_window(&rend) != 0)
	{
		return (1);
	}
	if (start_rend(rend) != 0)
	{
		return (1);
	}

	return (0);
}