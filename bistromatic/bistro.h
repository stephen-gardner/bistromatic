/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bistro.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:49:48 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/08 23:31:10 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BISTRO_H
# define BISTRO_H
# include "libft.h"
#include <stdio.h> // REMOVE BEFORE COMPLETION

typedef struct	s_digit
{
	int				n;
	struct s_digit	*next;
}				t_digit;

typedef struct	s_num
{
	t_digit	*digits;
	int		sign;
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
t_bool			read_digit(t_num *num, char c);
void			reverse_num(t_num *num);

/*
** ops.c
*/

t_num			*add_num(t_num *n1, t_num *n2);
#endif
