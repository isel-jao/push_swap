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
		return (rotate(a, RIGHT));
	if (!ft_strcmp(s, "rb"))
		return (rotate(b, RIGHT));
	if (!ft_strcmp(s, "rr"))
		return (rotate(a, RIGHT) & rotate(b, RIGHT));
	if (!ft_strcmp(s, "rra"))
		return (rotate(a, LEFT));
	if (!ft_strcmp(s, "rrb"))
		return (rotate(b, LEFT));
	if (!ft_strcmp(s, "rrr"))
		return (rotate(a, LEFT) & rotate(b, LEFT));

	return (1);
}