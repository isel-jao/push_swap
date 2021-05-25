#include "push_swap.h"

typedef struct s_vars
{
	int i;
	int r;
	int s;
	int med;
	int med_v;
} t_vars;

static void ft_sort_a(t_stack *a, t_stack *b, t_chunk chunk, t_vars v)
{
	
	v.med = get_median(a, v.s);
	v.med_v = a->arr[v.med].value;
	chunk.top++;
	chunk.indexes[chunk.top] = b->top + 1;
	v.i = a->top - v.s + 1;
	v.r = 0;
	while (--v.i >= 0)
	{
		if (a->arr[a->top].value <= v.med_v)
			apply_inst(a, b, "pb", 1);
		else if (++v.r)
			apply_inst(a, b, "ra", 1);
	}
	if (v.s > 0)
		while (v.r--)
			apply_inst(a, b, "rra", 1);
	if (a->top > v.s)
		sort_a(a, b, chunk);
	sort_b(a, b, chunk);
}

void sort_a(t_stack *a, t_stack *b, t_chunk chunk)
{
	t_vars v;

	v.s = get_last_sorted(a);
	if (v.s == -1 || a->top < v.s)
		return;
	if (a->top == v.s + 1 && a->arr[a->top].value > a->arr[v.s].value)
	{
		apply_inst(a, b, "sa", 1);
		sort_a(a, b, chunk);
		return;
	}
	ft_sort_a(a, b, chunk, v);
}

void sort_b(t_stack *a, t_stack *b, t_chunk chunk)
{
	t_vars v;

	if (b->top < 0)
		return;
	v.s = chunk.indexes[chunk.top];
	v.med = get_median(b, v.s);
	v.med_v = b->arr[v.med].value;
	v.i = b->top - v.s + 1;
	v.r = 0;
	while (--v.i >= 0)
	{
		if (b->arr[b->top].value >= v.med_v)
			apply_inst(a, b, "pa", 1);
		else if (++v.r)
			apply_inst(a, b, "rb", 1);
	}
	if (v.s > 0)
		while (v.r--)
			apply_inst(a, b, "rrb", 1);
	if (b->top < chunk.indexes[chunk.top])
		chunk.top--;
	sort_a(a, b, chunk);
	sort_b(a, b, chunk);
}