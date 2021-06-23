/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:12:08 by yqodsi            #+#    #+#             */
/*   Updated: 2021/06/23 18:35:24 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include "libft.h"

/*
** macro definition
*/

#define LEFT -1
#define RIGHT 1

#define TRUE 1
#define FALSE 0

#define OK 1
#define KO 0
#define ERROR -1

typedef struct s_data
{
	int value;
	int position;
} t_data;

typedef struct s_stack
{
	t_data *arr;
	int top;
} t_stack;

typedef struct s_chunk
{
	int *indexes;
	int top;
} t_chunk;

typedef struct s_all
{
	t_chunk chunks;
	t_stack a;
	t_stack b;
	t_data data;
} t_all;

typedef struct s_vars
{
	int count;
	int rot_count;
	int start;
	int med_index;
	int med_value;
} t_vars;

/*
** stack tools
*/

void push(t_stack *stack, t_data data);
t_data *pop(t_stack *stack);
int swap(t_stack *stack);
int rotate(t_stack *stack);
int reverse_rotate(t_stack *stack);

/*
** instruction
*/

int push_a(t_stack *a, t_stack *b);
int push_b(t_stack *a, t_stack *b);
int apply_inst(t_stack *a, t_stack *b, char *s, int print);

/*
**	parse 
*/

int ft_error(int exit_status);
int get_arg(char *arg, int *nb);
int is_duplicates(t_stack *a, int nb);
int parse(int ac, char **av, t_all *all);

/*
** sort_stack 
*/

int get_median(t_stack *stack, int low);
int first_unsorted(t_stack *stack);
void sort_a(t_stack *a, t_stack *b, t_chunk chunk);
void sort_b(t_stack *a, t_stack *b, t_chunk chunk);

void set_positions(t_stack *stack);
void free_tab(char **s);

#endif