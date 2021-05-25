#include "push_swap.h"


int ft_error(int exit_status)
{
	if (exit_status == OK)
	{
		ft_putendl("OK");
		return (0);
	}
	if (exit_status == KO)
	{
		ft_putendl("KO");
		return (0);
	}
	ft_putendl("Error");
	return (1);
}

int get_arg(char *arg, int *nb)
{
	int res;
	int b;

	b = 1;
	res = 0;
	if (*arg == '-')
		b = -1;
	if (*arg == '-' || *arg == '+')
		++arg;
	while (*arg && *arg >= '0' && *arg <= '9')
		res = res * 10 + (*arg++ - 48);
	if (*arg)
		return (1);
	*nb = ((int)res * b);
	return (0);
}

int is_duplicates(t_stack *a, int nb)
{
	int i;

	i = 0;
	while (i <= a->top)
	{
		if (a->arr[i].value == nb)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int parse(int ac, char **av, t_all *all)
{
	int nb;

	if (ac == 1)
		return 0;
	all->a.arr = malloc(sizeof(t_data) * (ac - 1));
	all->b.arr = malloc(sizeof(t_data) * (ac - 1));
	if (!all->a.arr || !all->b.arr)
		return (ft_error(ERROR));
	all->a.top = -1;
	all->b.top = -1;
	while (--ac >= 1)
	{
		if (get_arg(av[ac], &nb) || is_duplicates(&(all->a), nb))
		{
			free(all->a.arr);
			free(all->b.arr);
			return (ft_error(ERROR));
		}
		all->data.value = nb;
		push(&(all->a), all->data);
	}
	all->chunks.indexes = malloc(sizeof(int) * all->a.top);
	all->chunks.top = -1;
	return (OK);
}