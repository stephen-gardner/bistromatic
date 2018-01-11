/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 21:45:17 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/10 15:29:40 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bistro.h"

void	reverse_num(t_num *num)
{
	t_digit	*digit;
	t_digit	*prev;
	t_digit	*next;

	digit = num->start;
	num->end = digit;
	prev = NULL;
	while (TRUE)
	{
		next = digit->next;
		digit->next = prev;
		prev = digit;
		if (!next)
			break ;
		digit = next;
	}
	num->start = digit;
}

t_digit	*skip_zeroes(t_digit *digits)
{
	while (digits && digits->n == 0 && digits->next)
		digits = digits->next;
	return (digits);
}
