/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 21:49:59 by isel-jao          #+#    #+#             */
/*   Updated: 2021/05/28 12:23:47 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

float	ft_abs(float i)
{
	if (i >= 0)
		return (i);
	return (-i);
}

int	get_last_sorted(t_stack *stack)
{
	int	i;

	i = 0;
	while (stack->arr[i].position == i)
		i++;
	return (i);
}

float	get_middle(t_stack *stack, int low)
{
	int		min;
	int		max;
	int		i;

	min = stack->arr[low].value;
	max = stack->arr[low].value;
	i = low + 1;
	while (i <= stack->top)
	{
		if (stack->arr[i].value < min)
			min = stack->arr[i].value;
		if (stack->arr[i].value > max)
			max = stack->arr[i].value;
		i++;
	}
	return ((float)(min + max) / 2.);
}

int	get_median(t_stack *stack, int low)
{
	int		i;
	int		mid_index;
	float	middle;

	middle = get_middle(stack, low);
	mid_index = low;
	i = low + 1;
	while (i <= stack->top)
	{
		if (ft_abs((float)(stack->arr[i].value) - middle) <= \
		ft_abs((float)(stack->arr[mid_index].value) - middle))
			mid_index = i;
		i++;
	}
	return (mid_index);
}
