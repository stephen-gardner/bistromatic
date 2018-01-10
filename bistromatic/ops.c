/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 19:35:32 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/09 21:34:45 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

t_num	*add_num(t_calc *calc, t_digit *d1, t_digit *d2)
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

t_num	*sub_num(t_calc *calc, t_digit *d1, t_digit *d2)
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
