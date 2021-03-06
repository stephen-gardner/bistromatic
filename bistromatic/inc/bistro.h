/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bistro.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:49:48 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/15 07:00:52 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BISTRO_H
# define BISTRO_H
# include "libft.h"

typedef struct	s_calc
{
	char	*raw;
	char	*pos;
	char	*base;
	int		raw_len;
	int		nbase;
	t_stack	*stack;
	t_queue	*queue;
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

typedef enum	e_event
{
	DIGIT,
	NULL_TERM,
	PAREN_LEFT,
	PAREN_RIGHT,
	OP_AS,
	OP_MDM,
	SYNTAX_ERROR,
	NEVENTS
}				t_event;

typedef enum	e_state
{
	APPEND_NUM,
	COLLAPSE,
	CREATE_NUM,
	PUSH_TOKEN,
	QUIT,
	START,
	UNARY,
	NSTATES
}				t_state;

typedef struct	s_token
{
	char	type;
	void	*content;
}				t_token;

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
** fsm.c
*/

t_state			fsm_error(t_calc *calc);
void			fsm_run(t_calc *calc);

/*
** fsm_eval.c
*/

t_state			fsm_collapse(t_calc *calc);
t_state			fsm_eval(t_calc *calc);

/*
** fsm_num.c
*/

t_state			fsm_append(t_calc *calc);
t_state			fsm_create(t_calc *calc);

/*
** fsm_push.c
*/

t_state			fsm_push(t_calc *calc);

/*
** fsm_unary.c
*/

t_state			fsm_unary(t_calc *calc);
t_state			fsm_unary_paren(t_calc *calc);

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
t_bool			read_digit(t_calc *calc, t_num *num);

/*
** util.c
*/

void			*peek_end(t_queue *queue);
t_num			*strip_zeroes(t_num *num);
#endif
