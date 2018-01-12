/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arith_mul.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 15:53:15 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/12 00:22:55 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

static t_num	*mul_single(t_calc *calc, t_digit *d1, t_digit *d2, int pad)
{
	t_num	*res;
	int		carry;
	int		n;

	if (!(res = (t_num *)ft_memalloc(sizeof(t_num))))
		return (NULL);
	carry = 0;
	while (d1 || (n = carry))
	{
		if (d1)
		{
			n += (d1->n * d2->n);
			d1 = d1->prev;
		}
		carry = n / calc->nbase;
		if (!(prepend_digit(res, n % calc->nbase)))
			return (NULL);
	}
	while (pad--)
	{
		if (!(append_digit(res, 0)))
			return (NULL);
	}
	return (strip_zeroes(res));
}

static t_num	*mul_digits(t_calc *calc, t_digit *d1, t_digit *d2)
{
	t_num	*res;
	t_num	*single;
	t_num	*tmp;
	int		i;

	res = NULL;
	i = 0;
	while (d2)
	{
		if (!(single = mul_single(calc, d1, d2, i++)))
			return (NULL);
		if ((tmp = res))
		{
			if (!(res = add(calc, res, single)))
				return (NULL);
			destroy_num(tmp);
			destroy_num(single);
		}
		else
			res = single;
		d2 = d2->prev;
	}
	return (res);
}

t_num			*mul(t_calc *calc, t_num *n1, t_num *n2)
{
	t_num	*res;

	if ((res = mul_digits(calc, n1->end, n2->end)))
		res->sign = n1->sign * n2->sign;
	return (res);
}
