/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 13:16:41 by isel-jao          #+#    #+#             */
/*   Updated: 2021/05/23 13:54:11 by isel-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/includes/libft.h"

#define LEFT -1
#define RIGHT 1

#define TRUE 1
#define FALSE 0

#define OK 1
#define KO 0
#define ERROR -1

int g_lim = 0;
int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

typedef struct s_data
{
	int value;
	int position;
	int sorted;
} t_data;

typedef struct s_stack
{
	t_data *arr;
	int top;
} t_stack;

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
		stack->arr[stack->top].value = stack->arr[stack->top - 1].value;
		stack->arr[stack->top].position = stack->arr[stack->top - 1].position;
		ft_memmove(&(stack->arr[stack->top]), &(stack->arr[stack->top - 1]), sizeof(t_data));

		stack->arr[stack->top - 1].value = tmp.value;
		stack->arr[stack->top - 1].position = tmp.position;
	}
	return (0);
}

int rotate(t_stack *stack, int dir)
{
	t_data tmp;

	if (stack->top <= 0)
		return (0);
	if (dir == RIGHT)
	{
		ft_memmove(&tmp, &stack->arr[stack->top], sizeof(t_data));
		ft_memmove(stack->arr + 1, stack->arr, stack->top * sizeof(t_data));
		ft_memmove(&stack->arr[0], &tmp, sizeof(t_data));
	}
	if (dir == LEFT)
	{
		ft_memmove(&tmp, &stack->arr[0], sizeof(t_data));
		ft_memmove(stack->arr, stack->arr + 1, stack->top * sizeof(t_data));
		ft_memmove(&stack->arr[stack->top], &tmp, sizeof(t_data));
	}
	return (0);
}

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

int get_arg(char *arg, int *nb)
{
	int res;
	int b;

	b = 1;
	res = 0;
	if (*arg == '-')
		b = -1;
	if (*arg == '-' || *arg == '+')
		++arg;
	while (*arg && *arg >= '0' && *arg <= '9')
		res = res * 10 + (*arg++ - 48);
	if (*arg)
		return (1);
	*nb = ((int)res * b);
	return (0);
}

int check(char *arg, int *nb)
{
	int i;
	long int a;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (ft_isdigit(arg[i]))
		i++;
	if (arg[i])
		return (1);
	return (0);
}

int ft_error(int exit_status)
{
	if (exit_status == OK)
	{
		ft_putendl("OK");
		return (0);
	}
	if (exit_status == KO)
	{
		ft_putendl("KO");
		return (0);
	}
	ft_putendl("Error");
	return (1);
}

int check_sorted(int *stack_a, int len)
{
	int i;

	if (len == 1 || len == 2)
		return (1);
	i = 1;
	if (stack_a[i] > stack_a[i - 1])
	{
		while (++i < len)
		{
			if (stack_a[i] < stack_a[i - 1])
				return (0);
		}
		return (1);
	}
	while (++i < len)
	{
		if (stack_a[i] > stack_a[i - 1])
			return (0);
	}
	return (1);
}

int apply_inst(t_stack *a, t_stack *b, char *s)
{
	static int i;
	i++;
	// if (i > 1700)
	// 	exit(0);
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

int is_duplicates(t_stack *a, int nb)
{
	int i;

	i = 0;
	while (i <= a->top)
	{
		if (a->arr[i].value == nb)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int get_last_sorted(t_stack *stack)
{
	int i;

	i = 0;
	while (stack->arr[i].position == i)
		i++;
	return i;
}

typedef struct s_chunk
{
	int *indexes;
	int top;
} t_chunk;
float ft_abs(float i)
{
	if (i >= 0)
		return i;
	return (-i);
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

void sort_b(t_stack *a, t_stack *b, t_chunk chunk);
void sort_a(t_stack *a, t_stack *b, t_chunk chunk)
{
	int r = 0;
	int i;
	int start;
	int median;
	int median_value;
	int btop = b->top;
	start = get_last_sorted(a);
	if (start == -1 || a->top < start)
		return;
	if (a->top == start + 1 && a->arr[a->top].value > a->arr[start].value)
	{
		apply_inst(a, b, "sa");
		sort_a(a, b, chunk);
		return;
	}
	median = get_median(a, start);
	median_value = a->arr[median].value;
	// ft_putnbr(start);
	// ft_putstr("\t");
	// ft_putnbr(median);
	// ft_putstr("\t");
	// ft_putnbr(median_value);
	// ft_putendl("  sort_a");
	chunk.top++;
	chunk.indexes[chunk.top] = b->top + 1;
	i = a->top - start;
	while (i >= 0)
	{
		if (a->arr[a->top].value <= median_value)
			apply_inst(a, b, "pb");
		else if (++r)
			apply_inst(a, b, "ra");
		i--;
	}
	if (start > 0)
	{
		while (r--)
			apply_inst(a, b, "rra");
	}
	if (a->top > start)
		sort_a(a, b, chunk);
	sort_b(a, b, chunk);
}

void sort_b(t_stack *a, t_stack *b, t_chunk chunk)
{
	int r = 0;
	int i = 0;
	int start;
	int median;
	int median_value;
	if (b->top < 0)
		return;

	start = chunk.indexes[chunk.top];
	// median = start ;
	median = get_median(b, start);
	median_value = b->arr[median].value;
	// ft_putnbr(start);
	// ft_putstr("\t");
	// ft_putnbr(median);
	// ft_putstr("\t");
	// ft_putnbr(median_value);
	// ft_putendl("  sort_b");
	i = b->top - start;
	while (i >= 0)
	{
		if (b->arr[b->top].value >= median_value)
			apply_inst(a, b, "pa");
		else if (++r)
			apply_inst(a, b, "rb");
		i--;
	}
	if (start > 0)
	{
		while (r--)
		{
			apply_inst(a, b, "rrb");
		}
	}
	if (b->top < chunk.indexes[chunk.top])
		chunk.top--;
	sort_a(a, b, chunk);
	sort_b(a, b, chunk);
}

void print_stack(t_stack stack)
{
	int i;

	i = stack.top;
	printf("------\n");
	while (i >= 0)
	{
		printf("value %03d\tindex %03d\n", stack.arr[i].value, stack.arr[i].position);
		i--;
	}
	printf("------\n");
}
void selectionSort(t_stack *stack)
{
	int i;
	int j;
	int max;
	t_data tmp;

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

int get_index(t_stack *stack, int value)
{
	int index;

	index = 0;
	while (index <= stack->top)
	{
		if (stack->arr[index].value == value)
			return (index);
		index++;
	}
	return (-1);
}

void set_indexes(t_stack *stack)
{
	t_stack tmp;
	int i;

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

int main(int ac, char **av)
{
	t_stack a;
	t_stack b;
	t_data data;
	char inst[5];
	int i;
	int empty = TRUE;
	int sorted = FALSE;
	int nb;

	a.top = -1;
	b.top = -1;
	if (ac == 1)
		return 0;
	if (!(a.arr = malloc(sizeof(t_data) * (ac - 1))) || !(b.arr = malloc(sizeof(t_data) * (ac - 1))))
		return (ft_error(ERROR));
	i = ac - 1;
	while (i >= 1)
	{
		if (get_arg(av[i], &nb) || is_duplicates(&a, nb))
		{
			free(a.arr);
			return (ft_error(ERROR));
		}
		data.value = nb;
		push(&a, data);
		i--;
	}
	if (is_sorted(&a, &b))
		return (0);
	set_indexes(&a);
	t_chunk chunks;
	chunks.indexes = malloc(sizeof(int) * a.top);
	chunks.top = -1;
	// printf("median %d\n", a.arr[get_median(&a, 0)].value);
	sort_a(&a, &b, chunks);
}
