/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 19:35:32 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/10 22:16:46 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

static t_num	*get_max(t_num *n1, t_num *n2)
{
	t_digit	*d1;
	t_digit	*d2;

	if (n1->len == n2->len)
	{
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
	return ((n1->len > n2->len) ? n1 : n2);
}

static t_num	*add_num(t_calc *calc, t_digit *d1, t_digit *d2)
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
			d1 = d1->next;
		}
		if (d2)
		{
			n += d2->n;
			d2 = d2->next;
		}
		carry = (n >= calc->nbase) ? 1 : 0;
		append_digit(res, n % calc->nbase);
	}
	return (res);
}

static t_num	*sub_num(t_calc *calc, t_digit *d1, t_digit *d2)
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
			d1 = d1->next;
		}
		if (d2)
		{
			n -= d2->n;
			d2 = d2->next;
		}
		if ((carry = (n < 0) ? -1 : 0))
			n += calc->nbase;
		append_digit(res, n);
	}
	return (res);
}

t_num			*add(t_calc *calc, t_num *n1, t_num *n2)
{
	if (n2->sign < 0)
	{
		n2->sign = 1;
		return (subtract(calc, n1, n2));
	}
	if (n1->sign < 0)
	{
		n1->sign = 1;
		return (subtract(calc, n2, n1));
	}
	reverse_num(n1);
	reverse_num(n2);
	return (add_num(calc, n1->start, n2->start));
}

t_num			*subtract(t_calc *calc, t_num *n1, t_num *n2)
{
	t_num	*max;
	t_num	*res;

	if (n2->sign < 0)
	{
		n2->sign = 1;
		return (add(calc, n1, n2));
	}
	max = get_max(n1, n2);
	reverse_num(n1);
	reverse_num(n2);
	if (max == n1)
	{
		res = (n1->sign < 0)
			? add_num(calc, n1->start, n2->start)
			: sub_num(calc, n1->start, n2->start);
		res->sign = max->sign;
		return (res);
	}
	res = (n1->sign < 0)
		? add_num(calc, n2->start, n1->start)
		: sub_num(calc, n2->start, n1->start);
	res->sign = -1;
	return (res);
}
