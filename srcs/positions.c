/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 18:13:28 by isel-jao          #+#    #+#             */
/*   Updated: 2021/05/27 18:14:03 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	selectionSort(t_stack *stack)
{
	int		i;
	int		j;
	int		max;
	t_data	tmp;

	i = 0;
	while (i <= stack->top)
	{
		max = i;
		j = i + 1;
		while (j <= stack->top)
		{
			if (stack->arr[j].value > stack->arr[max].value)
				max = j;
			j++;
		}
		ft_memmove(&tmp, &(stack->arr[i]), sizeof(t_data));
		ft_memmove(&(stack->arr[i]), &(stack->arr[max]), sizeof(t_data));
		ft_memmove(&(stack->arr[max]), &tmp, sizeof(t_data));
		i++;
	}
}

static int	get_index(t_stack *stack, int value)
{
	int	index;

	index = 0;
	while (index <= stack->top)
	{
		if (stack->arr[index].value == value)
			return (index);
		index++;
	}
	return (-1);
}

void	set_positions(t_stack *stack)
{
	t_stack	tmp;
	int		i;

	tmp.arr = malloc(sizeof(t_data) * (stack->top + 1));
	ft_memmove(tmp.arr, stack->arr, sizeof(t_data) * (stack->top + 1));
	tmp.top = stack->top;
	selectionSort(&tmp);
	i = 0;
	while (i <= stack->top)
	{
		stack->arr[i].position = get_index(&tmp, stack->arr[i].value);
		i++;
	}
}
