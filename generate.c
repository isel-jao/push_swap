#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_list
{
	int key;
	struct s_list *next;
	struct s_list *prev;
} t_list;

void fill_list(t_list **numbers, int low, int hight)
{
	t_list *next;
	t_list *prev;
	prev = NULL;
	if (low < 0 || low < 0 || low > hight)
		return;
	while (low <= hight)
	{
		next = malloc(sizeof(t_list));
		next->key = low;
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		low++;
	}
	prev->next = NULL;
	*numbers = prev;
}

void print_list(t_list *numbers)
{
	if (numbers)
	{
		while (numbers->prev)
		{
			numbers = numbers->prev;
		}
		while (numbers)
		{
			printf("%d\n", numbers->key);
			numbers = numbers->next;
		}
	}
}

void pop_index(t_list **numbers, int index)
{
	int i;
	t_list *tmp;
	if (!numbers || !(*numbers))
		return;
	while ((*numbers)->prev)
		*numbers = (*numbers)->prev;
	if (index == 0)
	{
		printf("%d\n", (*numbers)->key);
		tmp = *numbers;
		*numbers = (*numbers)->next;
		if (*numbers)
			(*numbers)->prev = NULL;
		free(tmp);

		return;
	}
	i = 0;
	while (i < index && *numbers)
	{
		*numbers = (*numbers)->next;
		i++;
	}
	if (!(*numbers))
		return;
	printf("%d\n", (*numbers)->key);
	tmp = *numbers;
	*numbers = tmp->prev;
	(*numbers)->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = *numbers;
	free(tmp);
}
int min(int a, int b)
{
	if (a <= b)
		return a;
	return (b);
}
int main(int ac, char **av)
{
	t_list *numbers;
	int low;
	int hight;
	int size;
	
	if (ac == 4)
	{
		low = atoi(av[1]);
		hight = atoi(av[2]);
		size = atoi(av[3]);
		size = min(atoi(av[3]), hight - low + 1);
		if (low < 0 || hight < 0 || low > hight)
			return (1);
		numbers = NULL;
		fill_list(&numbers, low, hight);
		while (size > 0)
		{
			pop_index(&numbers, rand() % (size + 1));
			size--;
		}
	}
	else
		return (1);
	return (0);
}