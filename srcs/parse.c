/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 18:12:28 by isel-jao          #+#    #+#             */
/*   Updated: 2021/05/28 14:48:38 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_error(int exit_status)
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
	return (exit_status);
}

int	get_arg(char *arg, int *nb)
{
	long int	res;
	int			b;

	b = 1;
	res = 0;
	if (*arg == '-')
		b = -1;
	if (*arg == '-' || *arg == '+')
		++arg;
	while (*arg && *arg >= '0' && *arg <= '9')
	{
		res = res * 10 + (*arg++ - 48);
		if (res > 2147483647)
			return (1);
	}
	if (*arg)
		return (1);
	*nb = ((int)res * b);
	return (0);
}

int	is_duplicates(t_stack *a, int nb)
{
	int	i;

	i = 0;
	while (i <= a->top)
	{
		if (a->arr[i].value == nb)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	ft_parse(int *ac, char ***av)
{
	char	*arr;
	char	*tmp;
	int		i;

	arr = ft_strdup("");
	i = 0;
	while (i < *ac)
	{
		tmp = arr;
		arr = ft_strjoin(arr, *av[i]);
		free(tmp);
		tmp = arr;
		arr = ft_strjoin(arr, " ");
		free(tmp);
		i++;
	}
	*av = ft_split(arr, ' ');
	i = 0;
	while (*av[i])
		i++;
	*ac = i;
}

int	parse(int ac, char **av, t_all *all)
{
	int		nb;

	if (ac == 1)
		return (0);
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
