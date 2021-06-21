/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 21:36:31 by isel-jao          #+#    #+#             */
/*   Updated: 2021/06/03 13:17:49 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_tree(t_stack *a, t_stack *b)
{
	if (a->arr[0].position == 0)
    {
        if (a->arr[1].position != 1)
            apply_inst(a, b, "sa", 1);
    }
    else if (a->arr[1].position == 0)
    {
        apply_inst(a, b, "rra", 1);
        if (a->arr[1].position != 1)
            apply_inst(a, b, "sa", 1);
    }
    else
    {
        apply_inst(a, b, "ra", 1);
        if (a->arr[1].position != 1)
            apply_inst(a, b, "sa", 1);
    }
}

static void	sort_five(t_stack *a, t_stack *b)
{
	while (a->top > 2)
	{
		if (a->arr[a->top].position >= 3)
			apply_inst(a, b, "pb", 1);
		else
			apply_inst(a, b, "ra", 1);
	}
	sort_tree(a, b);
	while (b->top >= 0)
		apply_inst(a, b, "pa", 1);
	if (a->arr[a->top].value > a->arr[a->top - 1].value)
		apply_inst(a, b, "sa", 1);
}

static void	ft_sort_a(t_stack *a, t_stack *b, t_chunk chunk, t_vars v)
{
	v.med_index = get_median(a, v.start);
	v.med_value = a->arr[v.med_index].value;
	chunk.top++;
	chunk.indexes[chunk.top] = b->top + 1;
	v.count = a->top - v.start + 1;
	v.rot_count = 0;
	while (--v.count >= 0)
	{
		if (a->arr[a->top].value <= v.med_value)
			apply_inst(a, b, "pb", 1);
		else 
		{
			apply_inst(a, b, "ra", 1);
			v.rot_count++;
		}
	}
	if (v.start > 0)
		while (v.rot_count--)
			apply_inst(a, b, "rra", 1);
	if (a->top > v.start)
		sort_a(a, b, chunk);
	sort_b(a, b, chunk);
}

void	sort_a(t_stack *a, t_stack *b, t_chunk chunk)
{
	t_vars	v;

	if ((a->top == 4 || a->top == 3) && b->top == -1)
	{
		sort_five(a, b);
		return ;
	}
	if (a->top == 2)
		sort_tree(a, b);
	v.start = first_unsorted(a);
	if (a->top < v.start)
		return ;
	if (a->top == v.start + 1)
	{
		apply_inst(a, b, "sa", 1);
		return ;
	}
	ft_sort_a(a, b, chunk, v);
}

void	sort_b(t_stack *a, t_stack *b, t_chunk chunk)
{
	t_vars	v;

	if (b->top < 0)
		return ;
	v.start = chunk.indexes[chunk.top];
	v.med_index = get_median(b, v.start);
	v.med_value = b->arr[v.med_index].value;
	v.count = b->top - v.start + 1;
	v.rot_count = 0;
	while (--v.count >= 0)
	{
		if (b->arr[b->top].value >= v.med_value)
			apply_inst(a, b, "pa", 1);
		else if (++v.rot_count)
			apply_inst(a, b, "rb", 1);
	}
	if (v.start > 0)
		while (v.rot_count--)
			apply_inst(a, b, "rrb", 1);
	if (b->top < chunk.indexes[chunk.top])
		chunk.top--;
	sort_a(a, b, chunk);
	sort_b(a, b, chunk);
}
