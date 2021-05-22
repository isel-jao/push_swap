/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-jao <isel-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 13:16:41 by isel-jao          #+#    #+#             */
/*   Updated: 2021/05/22 12:58:12 by isel-jao         ###   ########.fr       */
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

// void print_stack(t_stack a, t_stack b)
// {
// 	int i;
// 	int j;
// 	i = ft_max(a.top, b.top);
// 	while (i >= 0)
// 	{
// 		if (i <= a.top)
// 			printf("%d\t", a.arr[i]);
// 		else
// 			printf("\t");
// 		if (i <= b.top)
// 			printf("%d \n", b.arr[i]);
// 		else
// 			printf("  \n");
// 		i--;
// 	}
// 	printf("- -\na\tb\n");
// 	printf("\n");
// }

int apply_inst(t_stack *a, t_stack *b, char *s)
{
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

// int get_min(t_stack *stack)
// {
// 	int min_index;
// 	int i;

// 	i = stack->top - 1;
// 	min_index = stack->top;
// 	while (i >= 0)
// 	{
// 		if (stack->arr[i] < stack->arr[min_index])
// 			min_index = i;
// 		i--;
// 	}
// 	return (min_index);
// }

// int get_max(t_stack *stack)
// {
// 	int min_index;
// 	int i;

// 	i = stack->top - 1;
// 	min_index = stack->top;
// 	while (i >= 0)
// 	{
// 		if (stack->arr[i] > stack->arr[min_index])
// 			min_index = i;
// 		i--;
// 	}
// 	return (min_index);
// }

void quickSortb(t_stack *a, t_stack *b, int low, int hight);
void quickSort(t_stack *a, t_stack *b, int low, int hight)
{
	int r;
	g_lim++;
	int btop = b->top;
	int median;
	int top_half;
	top_half = 0;
	int median_index;
	median = a->arr[low].value;
	median_index = 0;

	if (low >= hight)
		return;
	while (a->top > hight)
	{
		printf("pb\n");
		push_b(a, b);
	}

	int i;
	r = 0;
	i = 0;
	i = low;
	while (a->arr[a->top].value != median)
	{
		if (a->arr[a->top].value < median)
		{
			top_half++;
			push_b(a, b);
			printf("pb\n");
		}
		else
		{
			r++;
			apply_inst(a, b, "ra");
			printf("ra\n");
		}
		i++;
	}
	push_b(a, b);
	printf("pb\n");
	while (r--)
	{
		printf("rra\n");
		apply_inst(a, b, "rra");
	}
	printf("pa\n");
	push_a(a, b);
	while (b->top >= 0)
	{
		push_a(a, b);
		printf("pa\n");
	}
	quickSort(a, b, hight - top_half + 1, hight);
	// printf("low %d hight%d\n", low, hight);
	quickSort(a, b, low, hight - top_half - 1);
	// printf("low %d hight%d\n", low, hight);
}
// void quickSortb(t_stack *a, t_stack *b, int low, int hight)
// {
// 	int r;
// 	g_lim++;
// 	int btop = b->top;
// 	int median;
// 	int top_half;
// 	top_half = 0;
// 	int median_index;
// 	median = a->arr[low].value;
// 	median_index = 0;

// 	if (low >= hight)
// 	{
// 		push_b(a, b);
// 	}
// 	return;
// 	// while (a->top > hight)
// 	// {
// 	// 	printf("pb\n");
// 	// 	push_b(a, b);
// 	// }

// 	int i;
// 	r = 0;
// 	i = 0;
// 	i = low;
// 	while (a->arr[a->top].value != median)
// 	{
// 		if (a->arr[a->top].value > median)
// 		{
// 			top_half++;
// 			push_a(a, b);
// 			printf("pa\n");
// 		}
// 		else
// 		{
// 			r++;
// 			apply_inst(a, b, "rb");
// 			printf("rb\n");
// 		}
// 		i++;
// 	}
// 	push_b(a, b);
// 	printf("pb\n");
// 	while (r--)
// 	{
// 		printf("rra\n");
// 		apply_inst(a, b, "rra");
// 	}
// 	printf("pa\n");
// 	push_a(a, b);
// 	while (b->top >= 0)
// 	{
// 		push_a(a, b);
// 		printf("pa\n");
// 	}
// 	quickSort(a, b, hight - top_half + 1, hight);
// 	// printf("low %d hight%d\n", low, hight);
// 	quickSort(a, b, low, hight - top_half - 1);
// 	// printf("low %d hight%d\n", low, hight);
// }
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

void sort_b(t_stack *a, t_stack *b, t_chunk chunk);
void sort_a(t_stack *a, t_stack *b, t_chunk chunk)
{
	int r = 0;
	int i;
	int median;
	int median_value;
	int btop = b->top;
	median = get_last_sorted(a);
	median_value = a->arr[median].value;
	if (median == -1 || a->top < median)
		return;
	// // printf("--------------------------\n");
	if (a->top == median + 1)
	{
		if (a->arr[a->top].value > median_value)
		{
			apply_inst(a, b, "sa");
			printf("sa\n");
			sort_a(a, b, chunk);
			return;
		}
	}
	chunk.top++;
	chunk.indexes[chunk.top] = b->top + 1;
	i = a->top - median;
	while (i)
	{
		if (a->arr[a->top].value < median_value)
		{
			push_b(a, b);
			printf("pb\n");
		}
		else
		{
			r++;
			apply_inst(a, b, "ra");
			printf("ra\n");
		}
		i--;
	}
	push_b(a, b);
	printf("pb\n");
	while (r--)
	{
		printf("rra\n");
		apply_inst(a, b, "rra");
	}
	if (a->top > median)
		sort_a(a, b, chunk);
	sort_b(a, b, chunk);
}

void sort_b(t_stack *a, t_stack *b, t_chunk chunk)
{
	int r = 0;
	int i = 0;
	int median;
	if (b->top < 0)
		return;
	median = chunk.indexes[chunk.top];
	int median_value = b->arr[median].value;
	while (b->arr[b->top].value != median_value)
	{
		if (b->arr[b->top].value > median_value)
		{
			push_a(a, b);
			printf("pa\n");
		}
		else
		{
			r++;
			apply_inst(a, b, "rb");
			printf("rb\n");
		}
		i++;
	}
	push_a(a, b);
	printf("pa\n");
	while (r--)
	{
		printf("rrb\n");
		apply_inst(a, b, "rrb");
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

	sort_a(&a, &b, chunks);
}
