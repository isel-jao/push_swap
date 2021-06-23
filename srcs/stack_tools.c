/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 21:38:55 by yqodsi            #+#    #+#             */
/*   Updated: 2021/06/23 18:35:24 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void push(t_stack *stack, t_data data)
{
	stack->top++;
	ft_memmove(&(stack->arr[stack->top]), &data, sizeof(t_data));
}

t_data *pop(t_stack *stack)
{
	if (stack->top >= 0)
		return (&(stack->arr[stack->top--]));
	else
		return (NULL);
}

int swap(t_stack *stack)
{
	t_data tmp;

	if (stack->top >= 1)
	{
		ft_memmove(&tmp, &(stack->arr[stack->top]), sizeof(t_data));
		ft_memmove(&(stack->arr[stack->top]), &(stack->arr[stack->top - 1]),
				   sizeof(t_data));
		ft_memmove(&(stack->arr[stack->top - 1]), &tmp, sizeof(t_data));
	}
	return (0);
}

int rotate(t_stack *stack)
{
	t_data tmp;

	if (stack->top <= 0)
		return (0);
	ft_memmove(&tmp, &stack->arr[stack->top], sizeof(t_data));
	ft_memmove(stack->arr + 1, stack->arr, stack->top * sizeof(t_data));
	ft_memmove(&stack->arr[0], &tmp, sizeof(t_data));
	return (0);
}
int reverse_rotate(t_stack *stack)
{
	t_data tmp;

	if (stack->top <= 0)
		return (0);
	ft_memmove(&tmp, &stack->arr[0], sizeof(t_data));
	ft_memmove(stack->arr, stack->arr + 1, stack->top * sizeof(t_data));
	ft_memmove(&stack->arr[stack->top], &tmp, sizeof(t_data));
	return (0);
}
