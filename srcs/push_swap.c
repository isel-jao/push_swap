/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 13:16:41 by yqodsi            #+#    #+#             */
/*   Updated: 2021/06/23 18:35:24 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void print_stack(t_stack *stack)
{
	int i;

	i = stack->top;
	while (i >= 0)
	{
		ft_putnbr(stack->arr[i].value);
		ft_putstr("\t");
		ft_putnbr(stack->arr[i--].position);
		ft_putstr("\n");
	}
}

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

	all.a.arr = NULL;
	all.b.arr = NULL;
	all.chunks.indexes = NULL;
	if (ac == 1)
		return (0);
	if (parse(ac, av, &all) != OK)
		return (1);
	if (is_sorted(&(all.a), &(all.b)))
		return (0);
	set_positions(&(all.a));
	sort_a(&(all.a), &(all.b), all.chunks);
	ft_free(all.a.arr);
	ft_free(all.b.arr);
	ft_free(all.chunks.indexes);
	return (0);
}
