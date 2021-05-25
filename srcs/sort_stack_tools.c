#include "push_swap.h"


float ft_abs(float i)
{
	if (i >= 0)
		return i;
	return (-i);
}

int get_last_sorted(t_stack *stack)
{
	int i;

	i = 0;
	while (stack->arr[i].position == i)
		i++;
	return i;
}

int get_median(t_stack *stack, int low)
{
	int min;
	int max;
	float middle;
	int mid_index;
	min = stack->arr[low].value;
	max = stack->arr[low].value;
	for (int i = low + 1; i <= stack->top; i++)
	{
		if (stack->arr[i].value < min)
			min = stack->arr[i].value;
		if (stack->arr[i].value > max)
			max = stack->arr[i].value;
	}
	middle = (float)(min + max) / 2.;
	mid_index = low;
	for (int i = low + 1; i <= stack->top; i++)
	{
		if (ft_abs((float)(stack->arr[i].value) - middle) <= ft_abs((float)(stack->arr[mid_index].value) - middle))
			mid_index = i;
	}
	return (mid_index);
}