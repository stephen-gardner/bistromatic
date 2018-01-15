/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arith_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 19:35:32 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/12 21:51:27 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

static t_num	*get_max(t_num *n1, t_num *n2)
{
	t_digit	*d1;
	t_digit	*d2;

	if (n1->len != n2->len)
		return ((n1->len > n2->len) ? n1 : n2);
	d1 = n1->start;
	d2 = n2->start;
	while (d1 || d2)
	{
		if (!d1)
			return (n2);
		if (!d2)
			return (n1);
		if (d1->n != d2->n)
			return ((d1->n > d2->n) ? n1 : n2);
		d1 = d1->next;
		d2 = d2->next;
	}
	return (n1);
}

t_num			*sub(t_calc *calc, t_num *n1, t_num *n2)
{
	t_num	*max;
	t_num	*res;

	if (n2->sign < 0)
	{
		n2->sign = 1;
		return (add(calc, n1, n2));
	}
	max = get_max(n1, n2);
	if (max == n1)
	{
		res = (n1->sign < 0)
			? add_digits(calc, n1->end, n2->end)
			: sub_digits(calc, n1->end, n2->end);
		res->sign = max->sign;
		return (res);
	}
	res = (n1->sign < 0)
		? add_digits(calc, n2->end, n1->end)
		: sub_digits(calc, n2->end, n1->end);
	res->sign = -1;
	return (res);
}

t_num			*sub_digits(t_calc *calc, t_digit *d1, t_digit *d2)
{
	t_num	*res;
	int		carry;
	int		n;

	if (!(res = (t_num *)ft_memalloc(sizeof(t_num))))
		return (NULL);
	carry = 0;
	while (d1 || d2)
	{
		n = carry;
		if (d1)
		{
			n += d1->n;
			d1 = d1->prev;
		}
		if (d2)
		{
			n -= d2->n;
			d2 = d2->prev;
		}
		carry = (n < 0) ? -1 : 0;
		if (!(prepend_digit(res, (carry) ? n + calc->nbase : n)))
			return (NULL);
	}
	return (strip_zeroes(res));
}
