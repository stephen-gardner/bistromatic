/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arith_div.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 23:45:17 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/15 08:52:05 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

static int		get_quotient(t_calc *calc, t_num **n1, t_num *n2)
{
	int		quo;
	t_num	*tmp;

	if ((*n1)->len < n2->len)
		return (0);
	quo = 0;
	while (TRUE)
	{
		if (!(tmp = sub(calc, *n1, n2)))
			return (-1);
		if (tmp->sign < 0)
		{
			destroy_num(tmp);
			break ;
		}
		destroy_num(*n1);
		*n1 = tmp;
		quo++;
	}
	return (quo);
}

static t_num	*div_digits(t_calc *calc, t_num *n1, t_num *n2, t_num **remain)
{
	t_num	*res;
	t_num	*work;
	t_digit	*d1;
	int		quo;

	if (!(res = (t_num *)ft_memalloc(sizeof(t_num)))
		|| !(work = (t_num *)ft_memalloc(sizeof(t_num))))
		return (NULL);
	d1 = n1->start;
	while (d1)
	{
		if (!append_digit(work, d1->n)
			|| (quo = get_quotient(calc, &work, n2)) < 0
			|| !append_digit(res, quo))
			return (NULL);
		d1 = d1->next;
	}
	*remain = work;
	return (strip_zeroes(res));
}

t_num			*divide(t_calc *calc, t_num *n1, t_num *n2)
{
	t_num	*res;
	t_num	*remain;
	int		sign;

	sign = n1->sign * n2->sign;
	n1->sign = 1;
	n2->sign = 1;
	if (n2->len == 1 && n2->start->n == 0)
	{
		syntax_error();
		return (NULL);
	}
	if ((res = div_digits(calc, n1, n2, &remain)))
	{
		res->sign = sign;
		destroy_num(remain);
	}
	return (res);
}

t_num			*mod(t_calc *calc, t_num *n1, t_num *n2)
{
	t_num	*res;
	t_num	*remain;

	if (n2->len == 1 && n2->start->n == 0)
	{
		syntax_error();
		return (NULL);
	}
	if ((res = div_digits(calc, n1, n2, &remain)))
	{
		remain->sign = n1->sign * n2->sign;
		destroy_num(res);
	}
	return (remain);
}
