/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 13:16:41 by isel-jao          #+#    #+#             */
/*   Updated: 2021/05/28 14:43:04 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *a, t_stack *b)
{
	int	i;

	i = 0;
	if (b->top != -1)
		return (FALSE);
	while (i < a->top)
	{
		if (a->arr[i].value < a->arr[i + 1].value)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_all	all;
	char	*inst;

	if (parse(ac, av, &all) != OK)
		return (1);
	while (get_next_line(0, &inst))
	{
		if (apply_inst(&all.a, &all.b, inst, 0))
			return (ft_error(ERROR));
		free(inst);
	}
	if (!is_sorted(&all.a, &all.b))
		return (ft_error(KO));
	ft_putstr("OK\n");
	return (0);
}
