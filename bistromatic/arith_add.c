/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arith_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 19:35:32 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/11 23:36:14 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

t_num	*add(t_calc *calc, t_num *n1, t_num *n2)
{
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
	return (add_digits(calc, n1->end, n2->end));
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
		prepend_digit(res, n % calc->nbase);
	}
	return (strip_zeroes(res));
}
