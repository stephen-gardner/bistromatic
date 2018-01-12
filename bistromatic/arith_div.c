/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arith_div.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 23:45:17 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/11 23:51:08 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

static t_num	*div_digits(t_calc *calc, t_digit *d1, t_digit *d2)
{
	t_num	*res;

	res = NULL;
	return (res);
}

t_num			*div(t_calc *calc, t_num *n1, t_num *n2)
{
	t_num	*res;

	res = div_digits(calc, n1->start, n2->start);
	res->sign = n1->sign * n2->sign;
	return (res);
}
