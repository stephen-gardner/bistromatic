/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bistro.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:49:48 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/13 01:13:51 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BISTRO_H
# define BISTRO_H
# include "libft.h"
#include <stdio.h> // REMOVE BEFORE COMPLETION

typedef struct	s_calc
{
	char	*raw;
	char	*base;
	int		raw_len;
	int		nbase;
}				t_calc;

typedef struct	s_digit
{
	int				n;
	struct s_digit	*prev;
	struct s_digit	*next;
}				t_digit;

typedef struct	s_num
{
	t_digit	*start;
	t_digit	*end;
	int		sign;
	int		len;
}				t_num;

typedef struct	s_node
{
	void			*content;
	struct s_node	*next;
}				t_node;

typedef struct	s_stack
{
	t_node	*top;
}				t_stack;

typedef struct	s_queue
{
	t_node	*start;
	t_node	*end;
}				t_queue;

/*
** arith_add.c
*/

t_num			*add(t_calc *calc, t_num *n1, t_num *n2);
t_num			*add_digits(t_calc *calc, t_digit *d1, t_digit *d2);

/*
** arith_div.c
*/

t_num			*divide(t_calc *calc, t_num *n1, t_num *n2);
t_num			*mod(t_calc *calc, t_num *n1, t_num *n2);

/*
** arith_mul.c
*/

t_num			*mul(t_calc *calc, t_num *n1, t_num *n2);

/*
** arith_sub.c
*/

t_num			*sub(t_calc *calc, t_num *n1, t_num *n2);
t_num			*sub_digits(t_calc *calc, t_digit *d1, t_digit *d2);

/*
** ft_queue.c
*/

void			*dequeue(t_queue *queue);
t_bool			enqueue(t_queue *queue, void *content);
t_queue			*queue_init(void);
int				queue_isEmpty(t_queue *queue);
void			*queue_peek(t_queue *queue);

/*
** ft_stack.c
*/

t_stack			*stack_init(void);
t_bool			stack_isEmpty(t_stack *stack);
void			*stack_peek(t_stack *stack);
void			*stack_pop(t_stack *stack);
t_bool			stack_push(t_stack *stack, void *content);

/*
** main.c
*/

t_bool			syntax_error(void);

/*
** num.c
*/

t_bool			append_digit(t_num *num, int n);
void			destroy_num(t_num *num);
t_bool			prepend_digit(t_num *num, int n);
void			print_num(t_calc *calc, t_num *num);
t_num			*read_num(t_calc *calc, char *raw, int len);

/*
** util.c
*/

t_num			*strip_zeroes(t_num *num);
#endif
