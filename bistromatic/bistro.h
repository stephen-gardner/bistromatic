/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bistro.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:49:48 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/11 15:10:15 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BISTRO_H
# define BISTRO_H
# include "libft.h"
#include <stdio.h> // REMOVE BEFORE COMPLETION

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

typedef struct	s_calc
{
	char	*raw;
	char	*base;
	int		raw_len;
	int		nbase;
}				t_calc;

/*
** main.c
*/

t_bool			syntax_error(void);

/*
** num.c
*/

t_bool			append_digit(t_num *num, int n);
void			destroy_num(t_num **num);
t_bool			prepend_digit(t_num *num, int n);
void			print_num(t_calc *calc, t_num *num);
t_num			*read_num(t_calc *calc, char *raw, int len);

/*
** ops.c
*/

t_num			*add(t_calc *calc, t_num *n1, t_num *n2);
t_num			*sub(t_calc *calc, t_num *n1, t_num *n2);

/*
** util.c
*/

t_num			*strip_zeroes(t_num *num);
#endif
