/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arith_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 19:35:32 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/15 04:52:27 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

t_num	*add(t_calc *calc, t_num *n1, t_num *n2)
{
	t_num	*res;

	if (n2->sign < 0)
	{
		n2->sign = 1;
		return (sub(calc, n1, n2));
	}
	if (n1->sign < 0)
	{
		n1->sign = 1;
		return (sub(calc, n2, n1));
	}
	if ((res = add_digits(calc, n1->end, n2->end)))
		res->sign = 1;
	return (res);
}

t_num	*add_digits(t_calc *calc, t_digit *d1, t_digit *d2)
{
	t_num	*res;
	int		carry;
	int		n;

	if (!(res = (t_num *)ft_memalloc(sizeof(t_num))))
		return (NULL);
	carry = 0;
	while (d1 || d2 || carry)
	{
		n = carry;
		if (d1)
		{
			n += d1->n;
			d1 = d1->prev;
		}
		if (d2)
		{
			n += d2->n;
			d2 = d2->prev;
		}
		carry = n / calc->nbase;
		if (!(prepend_digit(res, n % calc->nbase)))
			return (NULL);
	}
	return (strip_zeroes(res));
}
