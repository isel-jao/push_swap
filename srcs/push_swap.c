/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yq <yq@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 13:16:41 by isel-jao          #+#    #+#             */
/*   Updated: 2021/05/25 18:02:14 by yq               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"



int is_sorted(t_stack *a, t_stack *b)
{
	int i;

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


int main(int ac, char **av)
{
	t_all all;

	if (parse(ac, av, &all) != OK)
		return (1);
	if (is_sorted(&(all.a), &(all.b)))
		return (0);
	set_positions(&(all.a));
	sort_a(&(all.a), &(all.b), all.chunks);
	free(all.a.arr);
	free(all.b.arr);
	free(all.chunks.indexes);
}
