/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 18:11:52 by yqodsi            #+#    #+#             */
/*   Updated: 2021/06/23 18:35:24 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int push_a(t_stack *a, t_stack *b)
{
	if (b->top > -1)
		push(a, *pop(b));
	return (0);
}

int push_b(t_stack *a, t_stack *b)
{
	if (a->top > -1)
		push(b, *pop(a));
	return (0);
}

int apply_inst(t_stack *a, t_stack *b, char *s, int print)
{
	if (print)
		ft_putendl(s);
	if (!strcmp(s, "sa"))
		return (swap(a));
	if (!ft_strcmp(s, "sb"))
		return (swap(b));
	if (!ft_strcmp(s, "ss"))
		return (swap(a) & swap(b));
	if (!ft_strcmp(s, "pa"))
		return (push_a(a, b));
	if (!ft_strcmp(s, "pb"))
		return (push_b(a, b));
	if (!ft_strcmp(s, "ra"))
		return (rotate(a));
	if (!ft_strcmp(s, "rb"))
		return (rotate(b));
	if (!ft_strcmp(s, "rr"))
		return (rotate(a) & rotate(b));
	if (!ft_strcmp(s, "rra"))
		return (reverse_rotate(a));
	if (!ft_strcmp(s, "rrb"))
		return (reverse_rotate(b));
	if (!ft_strcmp(s, "rrr"))
		return (reverse_rotate(a) & reverse_rotate(b));
	return (1);
}
