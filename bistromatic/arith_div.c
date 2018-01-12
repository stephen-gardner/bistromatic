/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arith_div.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 23:45:17 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/12 00:24:26 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

static int		get_multiplier(t_calc *calc, t_digit *d1, t_digit *d2)
{
	int		multi;
	t_num	*tmp;

	multi = 0;
	while (TRUE)
	{
		if (!(tmp = sub_digits(calc, d1, d2)))
			return (-1);

	}
}

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
