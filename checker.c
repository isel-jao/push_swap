/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yq <yq@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 13:16:41 by isel-jao          #+#    #+#             */
/*   Updated: 2021/05/25 18:02:31 by yq               ###   ########.fr       */
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

int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

typedef struct s_stack
{
	int *arr;
	int top;
} t_stack;

void push(t_stack *stack, int x)
{
	stack->top++;
	stack->arr[stack->top] = x;
}

int pop(t_stack *stack)
{
	if (stack->top >= 0)
		return (stack->arr[stack->top--]);
	else
		return (-1);
}

int swap(t_stack *stack)
{
	int tmp;

	if (stack->top >= 1)
	{
		tmp = stack->arr[stack->top];
		stack->arr[stack->top] = stack->arr[stack->top - 1];
		stack->arr[stack->top - 1] = tmp;
	}
	return (0);
}

int rotate(t_stack *stack, int dir)
{
	int tmp;

	if (stack->top <= 0)
		return (0);
	if (dir == RIGHT)
	{
		tmp = stack->arr[stack->top];
		ft_memmove(stack->arr + 1, stack->arr, stack->top * 4);
		stack->arr[0] = tmp;
	}
	if (dir == LEFT)
	{
		tmp = stack->arr[0];
		ft_memmove(stack->arr, stack->arr + 1, stack->top * 4);
		stack->arr[stack->top] = tmp;
	}
	return (0);
}

int push_a(t_stack *a, t_stack *b)
{
	if (b->top > -1)
		push(a, pop(b));
	return (0);
}

int push_b(t_stack *a, t_stack *b)
{
	if (a->top > -1)
		push(b, pop(a));
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

void print_stack(t_stack a, t_stack b)
{
	int i;
	int j;
	i = ft_max(a.top, b.top);
	while (i >= 0)
	{
		if (i <= a.top)
			printf("%d ", a.arr[i]);
		else
			printf("  ");
		if (i <= b.top)
			printf("%d \n", b.arr[i]);
		else
			printf("  \n");
		i--;
	}
	printf("- -\na b\n");
}

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
	int last;
	int new;

	if (b->top != -1)
		return (FALSE);
	if (a->top == 0)
		return (TRUE);
	last = pop(a);
	while (a->top >= 0)
	{
		new = pop(a);
		if (new < last)
			return (FALSE);
		last = new;
	}
	return (TRUE);
}

int is_duplicates(t_stack *a, int nb)
{
	int i;

	i = 0;
	while (i <= a->top)
	{
		if (a->arr[i] == nb)
			return (TRUE);
		i++;
	}
	return (FALSE);
}



int main(int ac, char **av)
{
	t_stack a;
	t_stack b;
	char *inst;
	int i;
	int empty = TRUE;
	int sorted = FALSE;
	int nb;

	a.top = -1;
	b.top = -1;
	if (ac == 1)
		return 0;
	if (!(a.arr = malloc(sizeof(int) * (ac - 1))) || !(b.arr = malloc(sizeof(int) * (ac - 1))))
		return (ft_error(ERROR));
	i = ac - 1;
	while (i >= 1)
	{
		if (get_arg(av[i], &nb) || is_duplicates(&a, nb))
		{
			free(a.arr);
			return (ft_error(ERROR));
		}
		push(&a, nb);
		i--;
	}
	inst = NULL;
	// while (get_line(&inst))
	// {
	// 	if (apply_inst(&a, &b, inst))
	// 		return (ft_error(ERROR));
	// 	free(inst);
	// }
	if (is_sorted(&a, &b))
		return (ft_error(OK));
	return (ft_error(KO));
}
